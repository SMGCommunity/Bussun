# Bussun
**Bussun** provides a framework for writing custom code injections in **Super Mario Galaxy 1**. With this, you will be able to link to existing functions and structures in the game and load your new code.

*Note:* Bussun is currently **work in progress**. Use at your own risk.

# What is supplied
Bussun provides symbols, kamek headers, and a custom code loader. *Why would anyone need these?*  
- Symbols - Used with [**Kamek**](https://github.com/Treeki/Kamek), these allow the new 
custom code to be linked against the game. These can be found for each region 
in `symbols/`
- Loader - New custom code needs to go somewhere in memory. The loader finds memory 
that can hold the new custom code and then adjusts the instructions to the new memory
addresses.
- Kamek headers - These are lifted directly from the [**Kamek**](https://github.com/Treeki/Kamek) repository and can be found at `"include/kamek/"`. 
They allow for custom code to overwrite particular symbols in the game.  
*Maybe coming soon: Tutorial on using kamek hooks with symbols so we don't end up with region-specific disaster hooks! (Hint: don't do what loader.cpp does!)*

# Limitations
Loader currently only works with one region (USA). This should maybe change soon...

# Requirements
In order to use this toolkit, you need to prepare some software and skills:

- The **CodeWarrior PPC EABI C/C++ Compiler**, preferrably application version 4.1 build 60126. For C files, other PPC compilers may work, but for C++, the CodeWarrior compiler is needed for ABI compatibility.
- A build of the [**Kamek**](https://github.com/Treeki/Kamek) linker.
- Knowledge of **C** / **C++** / **PowerPC**.
- **Python 3.11** or newer.
- A copy of [**Petari**](https://github.com/SMGCommunity/Petari)

# Building
Setup is easy. Put `mwcceppc.exe` in `"deps/CodeWarrior/"` and 
the `Kamek.exe`in `"deps/Kamek/"`. Place Petari in the same directory as Bussun, or modify 
its path in `build_loader.py`. Now, run 
`python build_loader.py [REGION] [-o output_path] [--full-xml]`.  

The following region targets exist:
- **PAL**: European/Australian releases
- **USA**: American releases
- **JPN**: Japanese releases
- **KOR**: Korean releases  

The loader riivolution patch can be found in `"loader/riivo_[REGION].xml"`.
To use loader, place a corresponding **Kamek File** binary containing your own code named 
`"CustomCode_[REGION].bin"` in the same folder as the riivolution patch.

# How make a mod basics
Set up your preferred build tools. Make sure to use the CodeWarrior compiler. Here is a [manual](https://www.nxp.com/docs/en/user-guide/CWPABTR.pdf). Make sure to use the 
[**Kamek**](https://github.com/Treeki/Kamek) linker and to pass the symbol map file from `"symbols/"` for the appropriate region. Also, include `"include/kamek/hooks.h"`.
To access headers for the game, include the paths from your local copy of [**Petari**](https://github.com/SMGCommunity/Petari). Then place the resulting CustomCode file into the same
folder as your riivolution patch for the loader.
