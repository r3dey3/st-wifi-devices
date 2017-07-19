# Installing
There are 2 ways of installing:

1. Integrating with GitHub
1. Copy and paste

## Integrating with GitHub
1. Follow the SmartThings documentation to [integrate with GitHub](http://docs.smartthings.com/en/latest/tools-and-ide/github-integration.html)
1. Log Into the SmartThings IDE ([US Users](https://graph.api.smartthings.com/), [UK Users](https://graph-eu01-euwest1.api.smartthings.com/))
1. Find the '**My Device Handlers**' link on the top of the page.
1. Find the **Settings** button at the upper-right corner of your SmartThings IDE page (this will only appear after you have configured with GitHub).
1. Clicking this button will open the GitHub Repository Integration page. Enter the information below:
   * Owner: r3dey3
   * Name: st-wifi-devices
   * Branch: master
1. Close the GitHub Repository Integration page by clicking the Save button.
1. Click the **Update from Repo** button at the upper-right corner of your SmartThings IDE and select 'st-wifi-devices' from the list.
1. In the right-hand column you will see two devicetypes/r3dey3/..., select both of them using the checkbox.
1. At the bottom-right corner of the **Update from Repo** page, select **Publish** using the checkbox and then click **Execute Update**.

## Copy and paste
1. The code for the Device Handlers:
   * [ContactSensor](https://raw.githubusercontent.com/r3dey3/st-wifi-devices/master/smartapps/r3dey3/devicetypes/r3dey3/wifi-contact-sensor.src/wifi-contact-sensor.groovy)
   * [Rest Switch](https://raw.githubusercontent.com/r3dey3/st-wifi-devices/master/smartapps/r3dey3/devicetypes/r3dey3/rest-switch.src/rest-switch.groovy)
1. Select all of the code (typically Ctrl+A) and copy it (typically Ctrl+C)
1. Next, log Into the SmartThings IDE ([US Users](https://graph.api.smartthings.com/), [UK Users](https://graph-eu01-euwest1.api.smartthings.com/))
1. Find the '**My Device Handlers**' link on the top of the page.
1. Click on the **+Create New Device Handler** in the upper-right corner.
1. Select the **From Code** tab along the top section.
1. Paste (typically Ctrl+V) the code you copied into the text box
1. Click the **Create** button in the bottom left corner
1. This will bring up another page with the code now formatted within the SmartThings IDE.
1. Click the **Save** button in the upper-right corner
1. Finally click-on the **Publish** button and select **For Me** at the upper-right corner of the screen.

