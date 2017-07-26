# WoodWhisperer Dust Deputy Sensor
This is a simple WiFi based sensor that behave like a contact sensor in SmartThings, but actually is a simple light level sensor.

Outside of device. Light sensor is where light enters to be detected
![Outside of device](images/outside.png?raw=true "Outside")

The one switch and sensitivity adjustment.
![Inside of device](images/diagram.png?raw=true "Location of switches and adjustment")

The three status lights.
![Status lights](images/lights.png?raw=true "Status lights inside device")

## WiFi Configuration
When the device is first turned on it will create a WiFi network "WWDustDSensor"; connecting to this network
will bring up a WiFi configuration page. Enter the settings for your WiFi network and hit save.

## Integration with Smart Things
1. You will need to Install both the [Simple Lan Device Manager](../smartapps/r3dey3/simple-lan-device-manager.src) and the 
[WiFi Contact Sensor](../devicetypes/r3dey3/wifi-contact-sensor.src). See those pages for installation instructions.
1. Once both are installed in the Web interface. Connect the sensor to your WiFi network if you haven't already
1. Go to the SmartApps in the SmartThings phone app
1. Click **Add a SmartApp**
1. Scroll down and select **My Apps**
1. Select **Simple LAN Device Manager**
1. After a few moments, it should say **Select Devices (1 found)**
1. Touch the Select Devices box and select the Checkbox next to **WoodWhisper Dust Deputy Light Sensor**
1. Touch **Done** in the upper right, which will return you to the Discovery Started Page.
1. Touch **Done** one more time. If everything was done correctly you should now have a new Thing in your list.

## Status LED
* 1 second blinks - The sensor is waiting for WiFi configuration. You have about 10 minutes to configure.
* 5 second blinks - Attempting to connect to the network (probably won't see this)
* Really fast blinking - Failed to configure network; restarting. This could occur if the configured network is down.
* 0.25 second blinks - Waiting for reset attempt.
* Off - connected to WiFi

## Power LED
* On if the device has power from a standard MicroUSB power cable.

## Light Detected LED and Sensitivity adjustment
* The LED lights up when the sensor detects light
* To adjust sensitivity up turn the screw clockwise; I suggest having the light on, and turning the sensitivity to where the sensor just detects the light; this will prevent false triggers from the lights in the shop. I tested with a bright flashlight in a daylight lit room and was able to adjust the sensitivity to where the sensor was not detecting light without the flashlight.

## Reset Configuration Switch
Unplug and plug the sensor back in. Once the Status LED starts blinking it the, push the 'Wipe Settings' button until the Status LED goes solid. If the Status LED goes solid then the settings have been reset. If LED continues to blink, the settings were not reset and you should try again.

# Electronics

## Parts list

* [WEMOS D1 Mini](https://wiki.wemos.cc/products:d1:d1_mini)
* [Light detection digital switch](http://a.co/c4E1IT5)
* [Tactile Switch Button (6mm slim)](https://www.adafruit.com/product/1489)

## Wiring
I was going to do a diagram/schematic but the wiring is so simple I can do it in 4 bullets.

* The switch is wired between pins D5 and D7.
* DO TTL of the light detector is wired to pin D2.
* GND of the light detector is wired to GND.
* VCC of the light detector is wired to 3V3.

# Software
The following libraries are used in addition to the standard Arduino software:

* ESP8266 - https://github.com/esp8266/Arduino
* WiFiManager - https://github.com/tzapu/WiFiManager
* ArduinoJson - https://github.com/bblanchon/ArduinoJson
