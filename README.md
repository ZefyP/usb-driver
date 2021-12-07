Test software for the Test Card for the PS-POH of the CMS Phase 2 Outer Tracker Upgrade.
The sotware makes use of the [CMSPh2_TCUSB library](https://gitlab.cern.ch/cms_tk_ph2/cmsph2_tcusb) and the [Power Supply control library](https://gitlab.cern.ch/cms_tk_ph2/power_supply). For the Power Supply library, one needs to currently use the [developer](https://gitlab.cern.ch/cms_tk_ph2/power_supply/-/tree/developer) branch now.

The structure of the repositories should be the following:
```
.
├── cmsph2_tcusb
├── power_supply
└── usb-driver
```

To build:

1. Build the `cmsph2_tcusb` and `power_supply` libraries following their respective instructions.
2. Go into `usb-driver`:
```
cd usb-driver/
``` 
3. Run `source setup.sh`.
4. Create the build directory:
```
mkdir build
```
5. Go into it and run `cmake`.
```
cd build
cmake ..
```
6. Check that both "Building the PowerSupply components" and "Building the TestCards USB components" are printed during the cmake output.
7. Run `make` on the build directory.
```
make -j8
```

8. To run the test use `pspoh`