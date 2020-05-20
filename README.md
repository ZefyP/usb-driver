To install and use with Ph2_ACF:
1. Clone project in Ph2_ACF's parent directory
2. Run make 
3. Run cmake and make again for the Ph2_ACF installation - make sure "Building the TestCards' USB components" is printed during cmake.
4. Give permissions to your user to access the CP2130 chip via usb :
-Run: sudo vim /etc/udev/rules.d/12-uib.rules
-Write the following: SUBSYSTEM=="usb", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="87a0", MODE="0660", GROUP="dialout"
-Run: sudo udevadm control --reload-rules && sudo udevadm trigger
-If you experience problems, PC restart or logging out and back in along with usb disconnection and then reconnection updates the permissions.