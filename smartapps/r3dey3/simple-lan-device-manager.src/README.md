# Simple LAN Device Manager

# Usage

# Installing
There are 2 ways of installing:

1. Integrating with GitHub
1. Copy and paste

## Integrating with GitHub
1. Follow the SmartThings documentation to [integrate with GitHub](http://docs.smartthings.com/en/latest/tools-and-ide/github-integration.html)
1. Log Into the SmartThings IDE ([US Users](https://graph.api.smartthings.com/), [UK Users](https://graph-eu01-euwest1.api.smartthings.com/))
1. Find the **My SmartApps** link on the top of the page.
1. Find the **Settings** button at the upper-right corner of your SmartThings IDE page (this will only appear after you have configured with GitHub).
1. Clicking this button will open the GitHub Repository Integration page. Enter the information below:
   * Owner: r3dey3
   * Name: st-wifi-devices
   * Branch: master
1. Close the GitHub Repository Integration page by clicking the Save button.
1. Click the **Update from Repo** button at the upper-right corner of your SmartThings IDE and select 'st-wifi-devices' from the list.
1. In the right-hand column you will see smartapps/r3dey3/simple-lan-device-manager.src/simple-lan-device-manager.groovy, select this using the checkbox. Do not select 'README.md'
1. At the bottom-right corner of the Update from Repo page, select **Publish** using the checkbox and then click **Execute Update**.
1. When done syncing, the new SmartApp should now appear in your IDE.

## Copy and paste
1. The code for the SmartApp can be found in [simple-lan-device-manager.groovy](https://raw.githubusercontent.com/r3dey3/st-wifi-devices/master/smartapps/r3dey3/simple-lan-device-manager.src/simple-lan-device-manager.groovy)
1. Select all of the code (typically Ctrl+A) and copy it (typically Ctrl+C)
1. Next, log Into the SmartThings IDE ([US Users](https://graph.api.smartthings.com/), [UK Users](https://graph-eu01-euwest1.api.smartthings.com/))
1. Find the **My SmartApps** link on the top of the page.
1. Click on the **+New SmartApp** in the upper-right corner.
1. Select the **From Code** tab along the top section.
1. Paste (typically Ctrl+V) the code you copied into the text box
1. Click the **Create** button in the bottom left corner
1. This will bring up another page with the code now formatted within the SmartThings IDE.
1. Click the **Save** button in the upper-right corner
1. Finally click-on the **Publish** button and select **For Me** at the upper-right corner of the screen.

# Development Interface

## SSDP
Discovery is performed using SSDP using a schema of `urn:schemas-upnp-org:device:st-wifi-dev`. Once discovered, the returned LOCATION is requested to retrieve the device description.

The device description can be the [standard UPNP basic device XML](http://upnp.org/specs/basic/UPnP-basic-Basic-v1-Device.pdf) or a JSON dictionary with the same keys as the device element in the XML schema.

When the device is discovered, the friendlyName field is what is presented to the User. If the friendlyName isn't present then the modelName is used. When the user adds the device, the manufacturer is used as the namespace and the deviceModel is used as the name. This allows for easy integration with multiple device types without the user having to change the type themselves.

## State Pushes
To handle state pushes:
1. The Device Handler must send the device the callback URL. This URL can be obtained using
   * `"http://" + parent.GetCallBackAddress(device.hub) + "/"`
   * Or, you can use `parent.SUBSRIBE(this, "REMOTE_PATH", device.hub)` to send the HTTP `SUBSCRIBE` method to REMOTE_PATH with the callback address in the `CALLBACK` header.
1. Once the device has the callback URL it can make POST requests which will be passed to the parseResponse method of the device handler. (it also hits the parse method, but you can't update state when that happens)
   * The `parseResponse` method takes a single Response Argument. This response is a parsed LAN response (using `parseLanMessage`) with the post data in either resp.json or resp.xml or resp.body.
1. To update values in the `parseResponse` method use `sendEvent()`


## Helper Methods
In all the helper methods for use by a device handler, the `device` parameter should be `this`

### `parent.GET(device, URL)`
Retrieve a url

### `parent.POST(device, URL, args)`
POST args to URL. If args is a string it is treated as the body, if it's a map, it will be sent as JSON

### `parent.SUBSCRIBE(device, URL, hub, args)`
Send a SUBSCRIBE HTTP method to URL, with the callback address in the CALLBACK HTTP header. args is any extra data (treated same as POST)
