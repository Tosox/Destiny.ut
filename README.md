# Destiny.ut
[![C++](https://img.shields.io/badge/Language-C%2B%2B-%23f34b7d.svg?style=flat)](https://en.wikipedia.org/wiki/C%2B%2B) 
[![CS:GO](https://img.shields.io/badge/Game-CS%3AGO-yellow.svg?style=flat)](https://store.steampowered.com/app/730/CounterStrike_Global_Offensive/) 
[![Windows](https://img.shields.io/badge/Platform-Windows-0078d7.svg?style=flat)](https://en.wikipedia.org/wiki/Microsoft_Windows) 
[![x86](https://img.shields.io/badge/Arch-x86-red.svg?style=flat)](https://en.wikipedia.org/wiki/X86) 

> This is not a ready-to-use cheat and as such it is highly recommended that you do not use this. 

## Disclaimer
[This programm](https://github.com/TosoxDev/Destiny.ut) is for educational purposes only!

Copyright Disclaimer under section 107 of the Copyright Act 1976, allowance is made for “fair use” for purposes such as criticism, comment, news reporting, teaching, scholarship, education and research.

## Features
*   **Aimbot** - Aim Assistance
*   **Triggerbot** - Automatically fires when crosshair is on enemy
*   **RCS** - Automatic recoil control 
*   **Glow** - Render glow effect on players
*   **Color Chams** - Color player models to improve visibility
*   **Misc** - Miscellaneous features
*   **Customization** - Change the settings to your liking

## FAQ
### The cheat crashes on startup
Make sure that [CS:GO](https://store.steampowered.com/app/730/CounterStrike_Global_Offensive/) is running and the cheat up-to-date.

### The features do not work
Make certain that the cheat creates an [offsets.json](https://github.com/TosoxDev/Destiny.ut/blob/master/src/offsets.json) file.

### The [offsets.json](https://github.com/TosoxDev/Destiny.ut/blob/master/src/offsets.json) file is empty
Check your network connection or try starting the program with a link to the [blazedumper dump](https://raw.githubusercontent.com/Akandesh/blazedumper/master/csgo.json)
as first parameter to download its offsets.

### Can I bring the menu to front?
Yes, press <kbd>INSERT</kbd> to bring the window to front.

### How do I unload the cheat?
Press <kbd>END</kbd> to unload it.

### I can't compile the source code
Make sure that you use `Debug | x86` as build configuration.

### Compiling still gives me errors
Ensure that you included the [lib](https://github.com/TosoxDev/Destiny.ut/tree/master/lib) directory in the project settings.

### Will the cheat be updated in the future?
No new features are likely to be added, however bug fixes and code improvements can be expected.

## Known Issues
- Some of the code is unoptimized.
- The visibility check is unreliable.
- There is a possibility that the cheat will not work immediately after new [CS:GO](https://store.steampowered.com/app/730/CounterStrike_Global_Offensive/) 
  updates, because [hazedumper's offsets](https://github.com/frk1/hazedumper) have not been updated yet. -> [Fix](#FAQ)

## Credits
- [ocornut](https://github.com/ocornut) for [Dear ImGui](https://github.com/ocornut)
- [hazedumper](https://github.com/frk1/hazedumper)  for providing the offsets
- [GLFW team](https://www.glfw.org/) for their easy-to-use library
- [nlohmann](https://github.com/nlohmann) for a modern C++ [implementation of JSON](https://github.com/nlohmann/json)
- and a special thanks to the [GuidedHacking](https://guidedhacking.com/) community