
# Arduino OOP Components

[![Commitizen friendly](https://img.shields.io/badge/commitizen-friendly-brightgreen.svg)](http://commitizen.github.io/cz-cli/)

A fully functional code library with many implementations of electronic components to ease readability and modifications for future changes. Made with C++ OOP with .h-only files 

## INDEX

* [REQUIREMENTS](#requirements)
* [DESCRIPTION](#description)
* [DISCLAIMER](#disclaimer)
* [EMOJIS](#emojis)
* [INSTALLING](#installing)
* [UPLOAD](#running)
* [TESTS](#tests)
* [ENVIRONMENT VARIABLES](#environment-variables)
* [COMMANDLINE](#commandline)

# REQUIREMENTS 
[goto index](#index)

VSCODE - https://code.visualstudio.com/

PlatformIO - https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide


# DESCRIPTION 
[goto index](#index)

This project started as a learning process for a VSCODE extension called [`PlatformIO IDE`](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide).

The biggest incentive was to migrate from Arduino IDE to a more robust code editor. 

## DISCLAIMER
[goto index](#index)

The codes found here are just pieces I wrote for my personal projects and felt like it could be useful later.

Most of it may or may not be bad examples. They work for my purposes and are all results of a good amount of time spent re-learning C++ and it's compilers.

There are `dynamic allocations` and I am trying to write all of it following the `S.O.L.I.D.` principles. 
I do know that many developers are against use of OOP for embeeded microchips, but the code does not aim to be the final form of anything. 
And I made a non OOP example with ease just by copying and pasting the OOP ones, so everything here can be used for prototyping.


As this repository grows, many new components will be added and later surely it will need some reorganizing.
If you know how those components works, you can build the circuit by yourself.

`example classes` are the place to put your own code, it is just for organization purposes.
- Pins are always defined inside the `example classes` for the simplicity of readability.
- All examples are instantiated into the `main.cpp` file.

`implementations` combines a specific library/logic to work with a component or feature of the board.

`translators` translates a real component and it's behaviour to code.

`helpers` contains code that does not belong to a specific scenario yet, most of it should be moved to specific folders within time.

`controllers` are places to put together components interaction logics.


Since this project does not target a specific project/purpose, many examples can be built, so the `main.cpp` will be constantly modified to adequate the most recent examples, or the ones I use the most.


## EMOJIS 
[goto index](#index)

[Lista de emojis](https://emojis.github.io/index.html)


## INSTALLING
[goto index](#index)

After downloading and installing all requirements, the only step left is to build and download the PlatformIO requirements defined on the .ini file.

## UPLOAD
[goto index](#index)

Follow PlatformIO tutorials (remember to select the correct environment variable for each programming board/microchip).

## TESTS
[goto index](#index)


## ENVIRONMENT VARIABLES
[goto index](#index)

|name|desc.|
|---|---|
|uno|For Arduino UNO boards.|
|esp12e|For ESP12E boards.|
|nodemcu|For NodeMCU boards.|

## COMMANDLINE
[goto index](#index)
