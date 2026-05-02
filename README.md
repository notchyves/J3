# J3
Minecraft for Windows mod manager

[![Discord server](https://img.shields.io/badge/chat-on%20discord-7289da.svg)](https://jiayisoftware.github.io/discord)

## Development status
This will be a complete remake of [Jiayi Launcher](https://github.com/JiayiSoftware/JiayiLauncher), matching most of its feature set and iterating upon some features. J3 is currently under **heavy development**.

## Features (planned)
* Written from the ground up in C++ using other open source libraries for reliability and performance
* Simple, clean, and customizable user interface
* Manage and run internal and external mods/clients, local or on the internet
* Switch between versions and view release notes with the version manager
* Create and restore backups of your game data

## Installation
Due to the mod manager being so incomplete, there is currently no way for an end user to easily install J3.

We plan to package releases in the APPX/MSIX format for simple installation and well-defined system permissions.

## Building
If you'd like to, you can clone this repository and build J3 yourself with the instructions below.

### Requirements
* A computer running Windows 10 or 11
* [Git](https://git-scm.com/)
* Windows SDK and build tools, retrieved by installing [Visual Studio](https://visualstudio.microsoft.com/vs/) with the `Desktop development with C++` package
  * This means you'll be building with MSVC, but `clang-cl` works as well (we use it for release builds)
* CMake >= 3.30
* An IDE that supports building CMake projects
  * We highly recommend using [CLion](https://www.jetbrains.com/clion/), but the aforementioned Visual Studio should work, given you have CMake support installed
  * You can omit this step if you prefer to not use an IDE and you know what you're doing

### Steps
1. Clone the repository
* ```git clone https://github.com/JiayiSoftware/J3.git```

2. Open the folder in your IDE
3. Build the project

## Contributing
If you want to contribute to J3, you can fork the repository and submit a pull request. Please join our Discord server above for a guide of our custom app framework.

The code is admittedly a mess, hence why there is no code style to adhere to. However, please try to keep the code clean and readable.

## License
J3 is released under the GNU General Public License, version 3.0. You can read the license [here](https://github.com/JiayiSoftware/J3/blob/master/LICENSE).

This is a summary of the license:
- You can modify, share and sell the code any way you please
- ...but you have to open source projects that do this under a compatible GPL license
- Any changes should be documented

If you bought this program, you were scammed!
