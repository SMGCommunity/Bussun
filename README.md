# Bussun
**Bussun** provides a framework for writing custom code injections in **Super Mario Galaxy 1**. With this, you will be able to write code, compile code, link to existing functions and structures in the game and load the actual changes. Due to a lack of C++ headers, they are currently being borrowed from [Petari](https://github.com/SMGCommunity/Petari).

*Note:* Bussun is currently **work in progress**. Use at your own risk.

# What is supplied
Bussun provides C++ headers, symbols and sample C++ code files.

- **PauseMenuNewButton.cpp**: This is a sample file that adds a new button to the Pause Menu which restarts the stage.
- **Util.cpp** and **Util.h**: Here, functions will be defined that can be used by any code added to the source/ folder.
- **Petari**: This is where the headers are being pulled from. They can be found in the include/ folder.
- **ModifiedAssets**: This is where files for the PauseMenuNewButton sample are kept.

# Future Plans
Currently, the framework is very limited and cannot make new LiveActors, for example. Including this and making this just as capable as [Syati](https://github.com/SMGCommunity/Syati) is the goal.

# Requirements
In order to use this toolkit, you need to prepare some software and skills:

- The **CodeWarrior PPC EABI C/C++ Compiler**, preferrably application version 4.3.0.172. There is also a free version of that compiler, but you may have to modify the compiler options in the two build scripts.
- A build of the [**Kamek**](https://github.com/Treeki/Kamek) linker.
- Knowledge of **C** / **C++** / **PowerPC**.
- **Python 3.7** or newer.

# Building
Setup is easy. Put the CodeWarrior files (*mwcceppc.exe*, etc.) in ``deps/CodeWarrior`` and the Kamek files in ``deps/Kamek``. Now, try to run the build scripts to check if they recognize the tools.

Provided you have all the requirements set up, building is very easy. To build a binary of your new custom code, run:
```python build.py REGION```, where REGION is the game's target region to build for.

To build the loader, run this instead:
```python buildloader.py REGION```, where REGION is, again, the target region to build for.

The following region targets exist:
- **PAL**: European/Australian releases
- **USA**: American releases
- **JPN**: Japanese releases
- **TWN**: Taiwanese releases
- **KOR**: Korean releases

The generated XML patches for Riivolution can be found in the *bin* folder.
