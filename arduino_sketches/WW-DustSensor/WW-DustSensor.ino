/**
 *  Copyright 2017 Kenny K
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 *  in compliance with the License. You may obtain a copy of the License at:
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
 *  on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
 *  for the specific language governing permissions and limitations under the License.
 *
 */

//Ticker for user feedback
#include <Ticker.h>
//EEPROM to save settings
#include <EEPROM.h>
//HTTP client and server for communication
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
// SSDP for discovery
#include <ESP8266SSDP.h>
//Wifi and WifiManager for setup
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
//DNS server because it's needed
#include <DNSServer.h>

//For parsing post data
#include <ArduinoJson.h>

ESP8266WebServer HTTP(80);

//Where to send changes
String callbackUrl;

/******************************************************************************
 * Tracking and Sending State
 */
#define PIN D2
#define RESET_SETTINGS_PIN D5
#define RESET_SETTINGS_PIN2 D7

//Last read pin value and change time
int LastValue;
unsigned long LastChangeTime;

//Cheating at JSON messages
const String CLOSED_MSG("{\"contact\":\"closed\"}");
const String OPENED_MSG("{\"contact\":\"open\"}");

void SendState(int val) {
	String json;

	if (callbackUrl.length() == 0) {
		return;
	}
	//Contact is 1 when the light is off.. also the same as a NO switch
	if (val) {
		json = CLOSED_MSG;
	}
	else {
		json = OPENED_MSG;
	}

	HTTPClient http;
	http.begin(callbackUrl);
	http.addHeader("Content-Type", "application/json");
	int code = http.POST(json); 
	Serial.printf("POST Returned %d\n", code);
	http.end();
}

/******************************************************************************
 * Handling Persistence of callback
 */

typedef struct {
	char ssid[36];
	char callback[1028];
} Settings_T;

void GetSavedCallback() {
	Settings_T settings;
	int len;
	EEPROM.get(0, settings);
	
	if (WiFi.SSID() == settings.ssid) {
		callbackUrl = settings.callback;
		Serial.print("Loaded callback ");
		Serial.println(callbackUrl);
	}
}

void SaveCallback(String callback) {
	Settings_T settings;
	if (callback != callbackUrl) {
		callbackUrl = callback;
		Serial.print("NEW CALLBACK: ");
		Serial.println(callbackUrl);

		memcpy(settings.ssid, WiFi.SSID().c_str(), WiFi.SSID().length()+1);
		memcpy(settings.callback, callback.c_str(), callback.length()+1);
		EEPROM.put(0, settings);
		EEPROM.commit();
	}
}

void ResetSettings() {
	Settings_T settings;
	memset(&settings, 0, sizeof(settings));
	EEPROM.put(0, settings);
	EEPROM.commit();
}
/******************************************************************************
 * Wifi Configuration
 */
Ticker LedTicker;

//gets called when WiFiManager enters configuration mode
void WifiConfigModeCallback (WiFiManager *myWiFiManager) {
	Serial.println("Entered config mode");
	Serial.println(WiFi.softAPIP());
	//if you used auto generated SSID, print it
	Serial.println(myWiFiManager->getConfigPortalSSID());

	//entered config mode, make led toggle faster
	LedTicker.attach(1, tick);
}
void tick()
{
	//toggle state
	int state = digitalRead(BUILTIN_LED);  // get the current state of GPIO1 pin
	digitalWrite(BUILTIN_LED, !state);     // set pin to the opposite state
}

void ConnectWifi() {
	//set led pin as output
	pinMode(BUILTIN_LED, OUTPUT);

	WiFiManager wifiManager;
	
	//fast-ish blink for waiting for reset
	LedTicker.attach(0.25, tick);

	Serial.println("Checking for reset");

	pinMode(RESET_SETTINGS_PIN, INPUT_PULLUP);
	pinMode(RESET_SETTINGS_PIN2, OUTPUT);
	digitalWrite(RESET_SETTINGS_PIN2, 0);

	for (int i = 0; i < 3*4; i++) {
		delay(250);
		if (digitalRead(RESET_SETTINGS_PIN) == LOW) {
			LedTicker.detach();
			wifiManager.resetSettings();
			digitalWrite(BUILTIN_LED, LOW);    

			ResetSettings();
			delay(5000);
			ESP.restart();
			delay(1000);
		}
	}

	pinMode(RESET_SETTINGS_PIN, INPUT);
	pinMode(RESET_SETTINGS_PIN2, INPUT);
	//start a really slow blink for connecting
	LedTicker.attach(5, tick);

	//set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
	wifiManager.setAPCallback(WifiConfigModeCallback);  

	//sets timeout until configuration portal gets turned off
	wifiManager.setTimeout(15 * 60);

	//Configure WiFi Network
	if (!wifiManager.autoConnect("WWDustDSensor")) {
		Serial.println("failed to connect and hit timeout");
		LedTicker.attach(0.05, tick);

		delay(5000);
		ESP.restart();
		delay(1000);
	}

	LedTicker.detach();
	//Turn LED off
	digitalWrite(BUILTIN_LED, HIGH);    
}

/******************************************************************************
 * Main code
 */
void setup() {
	Serial.begin(115200);
	Serial.println("\n Starting");
	EEPROM.begin(sizeof(Settings_T));
	
	//ResetSettings();

	ConnectWifi();

	GetSavedCallback();

	//Setup HTTP Server
	HTTP.on("/state.json", HTTP_GET, [](){
		if (LastValue) {
			HTTP.send(200, "application/json", CLOSED_MSG);
		}
		else {
			HTTP.send(200, "application/json", OPENED_MSG);
		}
	});

	HTTP.on("/description.xml", HTTP_GET, [](){
		Serial.println("Upnp query");
		SSDP.schema(HTTP.client());
	});

	HTTP.on("/subscribe", HTTP_POST, [](){
		Serial.println("Subscribe");

		DynamicJsonBuffer jsonBuffer(200);
		JsonObject& json = jsonBuffer.parseObject(HTTP.arg("plain"));
		if (!json.success()) {
			HTTP.send(500, "application/json", "{}");
		}
		else {
			SaveCallback(json["callback"]);
			HTTP.send(200, "application/json", "{}");
		}
	});

	HTTP.begin();

	/***** Setup SSDP */
	Serial.printf("Starting SSDP...\n");
	SSDP.setSchemaURL("description.xml");
	SSDP.setHTTPPort(80);
	SSDP.setName("WoodWhisperer Dust Deputy Light Sensor");
	SSDP.setURL("state.json");
	SSDP.setModelName("WiFi Contact Sensor");
	SSDP.setDeviceType("urn:schemas-upnp-org:device:st-wifi-dev");
	//SSDP.setDeviceType("urn:schemas-upnp-org:device:basic:1");
	SSDP.setManufacturer("r3dey3");
	//SSDP.setManufacturerURL("http://www.philips.com");
	SSDP.begin();

	/* Setup Input */
	pinMode(PIN, INPUT_PULLUP);
	LastChangeTime = millis();
	LastValue = digitalRead(PIN);

	/* Send the current state */
	SendState(LastValue);
}


/*****************************************************************************/
void loop() {
	// Handle and HTTP clients
	HTTP.handleClient();

	// Handle Input
	int value = digitalRead(PIN);

	if (value != LastValue && (millis() - LastChangeTime) > 1000 ) {
		Serial.println("Value changed");
		LastValue = value;
		LastChangeTime = millis();
		SendState(value);
	}
}
