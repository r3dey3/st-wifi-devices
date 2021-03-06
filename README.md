# SmartThings Local LAN Devices
SmartThings is very capable of finding WiFi and LAN devices on a local network,
as well as both querying status and receiving updates from the devices.
Most tutorials do not include appropriate information on how to push status to
the SmartThings hub as most of them include the IP and port in the device network
id, but in order to receive push data it needs to be the MAC address.

## Service Manager
[Simple Lan Device Manager](smartapps/r3dey3/simple-lan-device-manager.src) is
a SmartThings smartapp which handles device discovery as well as updating IP 
information in case it changes.

## Device Types
[Rest Switch](devicetypes/r3dey3/rest-switch.src) is a simple device type that
operates using JSON requests to query and change state.

[WiFi Contact Sensor](devicetypes/r3dey3/wifi-contact-sensor.src) is a simple contact
sensor device.

# Installation
See [devicetypes/README.md](devicetypes/README.md) for installing Device Types, and
[smartapps/r3dey3/simple-lan-device-manager.src/README.md](smartapps/r3dey3/simple-lan-device-manager.src/README.md)) for installing the SmartApp
