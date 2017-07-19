# WoodWhisperer Dust Deputy Sensor
This is a simple WiFi based sensor that behave like a contact sensor in SmartThings, but actually is a simple light level sensor.


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
1. Touch the Select Devices box and select the Checkbox next to **WoodWhispers Dust Deputy Light Sensor**
1. Touch **Done** in the upper right, which will return you to the Discovery Started Page.
1. Touch **Done** one more time. If everything was done correctly you should now have a new Thing in your list.

## LED
The LED is used as a status when connecting to the network
* 1 second blinks - The sensor is waiting for WiFi configuration. You have about 10 minutes to configure.
* 5 second blinks - Attempting to connect to the network (probably won't see this often)
* Really fast blinking - Failed to configure network; restarting. This could occur if the configured network is down.
* 0.25 second blinks - Waiting for reset attempt.


## Reset Configuration
Reset the sensor (unplug and plug back in, or hit reset button) once the LED starts blinking it the, click the 'Wipe Settings' button. If the LED goes solid then the settings have been reset. If the blink rate changes, then you need to try again.
