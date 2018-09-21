# Vape Firmware
This is the vape firmware based on mbed-os. The target is ```RBLAB_BLENANO```, however, we are using a ```WT51822_S4AT``` module.

## Preliminaries
1. Python 2.7 installed, optional: pip installed
2. ARM GCC installed
1. mbed cli installed: https://github.com/ARMmbed/mbed-cli
2. mbed cli requirements installed. See mbed-os' [```requirements.txt```](https://github.com/ARMmbed/mbed-os/blob/master/requirements.txt).

## Setup
1. Open a terminal and cd into your development folder e.g. /home/user/development
2. Run ```mbed import git@github.com:acidg/vape_mbed```
3. Go to checked out folder: ```cd vape_mbed```
4. Set correct path for GCC_ARM_PATH binary in ```mbed_settings.py``` (e.g. /usr/bin)
5. Compile: ```mbed compile```

## Develop
### IDE Integration
mbed-cli can be used to generate project files for IDEs such as Eclipse or Visual Studio Code: 
```mbed export -i vscode_gcc_arm```

### Adding libraries
mbed-cli can be used to ad a library using its shortname or url: 
```mbed add libraryname``` or ```mbed add http://...```
After adding a library, don't forget to add the library's folder to the ```.gitignore``` file and re-export the IDE project file.


## Flashing
1. Connect the STLink V2 Programmer to the board
2. Apply external power to the board 
3. Run ```sudo openocd -f openocd.cfg``` to start the openocd debugger
4. Connect to the debugger using telnet: ```telnet 127.0.0.1 4444```
5. Reset the board using the following command in the telnet cli: ```reset halt```
6. Flash the hex file using the following command in the telnet cli: ```program /path/to/hex/file.hex verify```

If you are using a pre-flashed module (such as the ```WT51822_S4AT```) you may need to run ```reset halt``` and ```nrf51 mass_erase``` first.

## Troubleshooting
This project uses the mbed 2 library instead of the latest mbed-os. This was achieved by intializing the project using ```mbed new vape_mbed --mbedlib```. This way, the mbed 2 library is downloaded into the ```mbed``` folder. Also, the mbed tools are downloaded into the ```.temp``` folder. However, when adding the mbed library using ```mbed add mbed```, the latest mbed-os is downloaded, and building failes. To get the mbed 2 library instead, remove the mbed-os using ```mbed remove mbed``` and revert the ```mbed.bld``` file. Then use ```mbed deploy``` to re-download all dependencies including the mbed 2 library.

When the export function is used to export a makefile (or for Visual Studio Code), the Makefile has to be changed. Quite at the end of the generated Makefile, ```srec_cat``` is called to concatenate the softdevice and the compiled hex file. The generation of the Makefile is faulty and includes multiple softdevices. Remove all hex files from the arguments of the ```srec_cat``` call, except the ```.../TARGET_RBLAB_BLENANO/.../s130_nrf51_1.0.0_softdevice.hex```to fix this.
