# Overview
This is a template repository for creating your own REL mod for the GameCube version of Paper Mario: The Thousand-Year Door.  

## Project Structure
```
TTYD_REL_Template
├───bin/                     // Binary files and scripts
│   ├───gcipack.py           // Packs a REL into a GCI
│   ├───readme.txt           // Explanation for where gcipack.py was retrieved from
├───docs/                    // Useful information for various things
│   ├───ttyd-opc-summary.txt // Clarifies which ttydasm mnemonic goes to which C macro mnemonic, specified by evt_cmd.h
│   ├───readme.txt           // Explanation for where ttyd-opc-summary.txt was retrieved from
├───images/                  // Banner and Icon files for the GCI, in RGB5A3 format
├───include/                 // Your Header (.h) files
│   ├───gc/                  // Header files that are specific to the GameCube SDK
│   ├───lst/                 // Symbol:Address pairs for each version of the game
│   ├───ttyd/                // Header files that are specific to vanilla TTYD
├───source/                  // Your Source (.cpp) files
│   ├───runtime/             // Assembly source files that are automatically used when needed
├───Makefile                 // Build script
├───.clang-format            // clang-format configuration file, intended to be used with VSCode
```

## Download
The latest release can be found on the [releases page](https://github.com/Zephiles/TTYD-REL-Template/releases).  

## Usage
The GCI is intended to be used with either the REL Loader gecko code (can be found [here](https://github.com/Zephiles/TTYD-Practice-Codes/tree/master/relloader/build/Gecko)), or the hacked savefile containing the REL Loader file (can be found [here](https://github.com/magcius/TTYDSaveHacker/releases)). A video tutorial for using either of these methods can be found [here](https://www.youtube.com/watch?v=h-cWbVogy6Q).

## Prerequisites
* `devkitPPC` (can be found [here](https://devkitpro.org/wiki/Getting_Started)). Note that **v47.1** was used to build this project. To find your exact version, navigate to `devKitPro\devkitPPC\bin` (the **devKitPro** folder should be where you chose to install **devkitPPC**) and run the following in a terminal such as Windows command prompt: `powerpc-eabi-gcc --version`. An example being that the version used to build this project is reported as `(devkitPPC release 47.1) 15.1.0`.  
* `Python 3` (can be found [here](https://www.python.org/downloads/)). Note that a minimum version of **3.9** is required to build this project (see below), and that **v3.13.1** was used to build this project. For Windows users, this will need to be installed from within the **mingw64** terminal that is included with **devkitPPC**, which is explained further in the [Building](#building) section below.   
* `pyelf2rel` (can be found [here](https://pypi.org/project/pyelf2rel/)). Requires a minimum Python version of **3.9**. Note that **v1.0.9** was used to build this project.  

## Building
For Windows users, **devkitPPC** comes with its own terminal that needs to be used for building projects. The specific one you want is `devKitPro/msys2/mingw64.exe` (the **devKitPro** folder should be where you chose to install **devkitPPC**).  

To build, you must first add **DEVKITPPC** to your environment, in which it should be set to the `devkitPPC` folder. You can then run `make` from a terminal to build the GCI files. Any combination of rules can be applied to this. You should also run `make clean` after making any changes, as files built with a previous build could cause issues.  

Examples of `make` being used:  
`make us`  
`make jp eu`  
`make us eu`  

The following is an example of building the project for the US version of the game:  
```shell
$ cd /c/Path/To/REL
$ make us
cxx.cpp
draw.cpp
main.cpp
patch.cpp
rel.cpp
restfpr_x.s
restgpr_x.s
linking ... TTYD_REL_Template.us.elf
output ... TTYD_REL_Template.us.rel
packing ... TTYD_REL_Template.us.gci
```

## VSCode
Due to the complexity of REL mods, it is recommended to use **VSCode** for working on them, which can be found [here](https://code.visualstudio.com/Download).  

To set it up, you first need to configure **VSCode** to work with C++. On the panel to the left, select **Extensions** (alternatively press `Ctrl + Shift + X` if on Windows). In the search bar, search for `ms-vscode.cpptools` and install it. You can also optionally install the `Better C++ Syntax` extension, which is found by searching for `jeff-hykin.better-cpp-syntax`.  

From here, you need to set up a configuration file for the project in order to get intellisense to work correctly. To do this, first open the root of the project via `File->Open Folder`. With the project open, go to `View->Command Palette` (alternatively press `Ctrl + Shift + P` if on Windows), and search for `C/C++: Edit Configurations (JSON)`. From here, the following configuration should work assuming you're on Windows, and that **devkitPPC** is installed to the root of the **C** drive:  
```
{
    "configurations": [
        {
            "name": "TTYD_REL_Template",
            "includePath": [
                "C:/devKitPro/devkitPPC/*",
                "${workspaceFolder}/include/*"
            ],
            "defines": [
                "TTYD_US=1"
            ],
            "cStandard": "c17",
            "cppStandard": "c++23",
            "intelliSenseMode": "gcc-x86",
            "compilerPath": "C:/devKitPro/devkitPPC/bin/powerpc-eabi-g++",
            "browse": {
                "limitSymbolsToIncludedHeaders": true
            }
        }
    ],
    "version": 4
}
```

After this is set, everything should work as expected. However, an important thing to note is that intellisense sometimes tends to break (including when changing anything in the configuration like above), in which case you can do a developer reload to reload the project. This can be found by going to `View->Command Palette` (alternatively press `Ctrl + Shift + P` if on Windows) and searching for `Developer: Reload Window`.  

## Credits
* [PistonMiner](https://github.com/PistonMiner) for their work on the TTYD scripting disassembly, the initial code for the rel framework, and the elf2rel, gcipack, and rellink utilities. (GitHub repo for these tools [here](https://github.com/PistonMiner/ttyd-tools).)  
* [Jdaster64](https://github.com/jdaster64) for their work on various TTYD modding projects, as well as creating the video tutorial for using REL mods.  
* [SeekyCt](https://github.com/SeekyCt) for their work on **pyelf2rel**, which adds additional functionality over the original **elf2rel**. 
* [kipcode66](https://github.com/kipcode66) for writing the Twilight Princess REL Template readme (can be found [here](https://github.com/zsrtp/REL/blob/master/README.MD)), in which portions of this readme are based on.  