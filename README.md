
# Arduino OOP Components

[![Commitizen friendly](https://img.shields.io/badge/commitizen-friendly-brightgreen.svg)](http://commitizen.github.io/cz-cli/)

A fully functional code library with many implementations of electronic components to ease readability and modifications for future changes. Made with C++ OOP with .h-only files 

## INDEX

* [REQUIREMENTS](#requirements)
* [DESCRIPTION](#description)
* [DISCLAIMER](#disclaimer)
* [EMOJIS](#emojis)
* [INSTALLING](#installing)
* [RUNNING](#running)
* [TESTS](#tests)
* [ENVIRONMENT VARIABLES](#variaveis-de-ambiente)
* [COMMANDLINE](#guia-de-comandos)

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

`example classes` are the entry point, containing the whole logic to be ran for each example.
Pins are always defined inside the `example classes` for the simplicity of readability.

All examples are instantiated into the `main.cpp` file.

`implementations` are generic forms of a component/feature present on the circuit.

`translators` are specific components, with logic to operate them correctly.

`helpers` contains code that does not belong to a specific scenario yet, most of it should be moved to specific folders within time.

`controllers` are places to put together components interaction logics.


Since this project does not target a specific project/purpose, many examples can be built, so the `main.cpp` will be constantly modified to adequate the most recent examples, or the ones I use the most.


## EMOJIS 
[goto index](#index)

[Lista de emojis](https://emojis.github.io/index.html)


## INSTALLING


## RUNNING


## TESTS


## ENVIRONMENT VARIABLES


## COMMANDLINE