# Bussun
**Bussun** provides a framework for writing custom code injections in **Super Mario Galaxy 1**. With this, you will be able to link to existing functions and structures in the game and load your new code.

*Note:* Bussun is currently **work in progress**. Use at your own risk.

# What is supplied
Bussun provides C++ headers, symbols and sample C++ code files.

- **Petari**: This is where the headers are being pulled from. They can be found in the include/ folder.

# Requirements
In order to use this toolkit, you need to prepare some software and skills:

- The **CodeWarrior PPC EABI C/C++ Compiler**, preferrably application version 4.3.0.172. For C files, other PPC compilers may work, but for C++, the CodeWarrior compiler is needed for ABI compatibility.
- A build of the [**Kamek**](https://github.com/Treeki/Kamek) linker.
- Knowledge of **C** / **C++** / **PowerPC**.
- **Python 3.11** or newer.

# Building
Setup is easy. Put the CodeWarrior files (*mwcceppc.exe*, etc.) in ``CodeWarrior`` and the Kamek files in ``Kamek``. Now, try to run the build scripts to check if they recognize the tools.

Provided you have all the requirements set up, building is very easy. To build a binary of your new custom code, run:
```python build.py REGION```, where REGION is the game's target region to build for.

The following region targets exist:
- **PAL**: European/Australian releases
- **USA**: American releases
- **JPN**: Japanese releases
- **KOR**: Korean releases

The generated XML patches for Riivolution can be found in the main folder of the repo when built.
