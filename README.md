
# Arduino OOP Components

[![Commitizen friendly](https://img.shields.io/badge/commitizen-friendly-brightgreen.svg)](http://commitizen.github.io/cz-cli/)

A fully functional code library with many implementations of electronic components to ease readability and modifications for future changes. Made with C++ OOP with .h-only files 

## INDEX

* [REQUIREMENTS](#requirements)
* [DESCRIPTION](#description)
* [THE CODE SO FAR](#the-code-so-far)
* [EMOJIS](#emojis)
* [INSTALLING](#installing)
* [RUNNING](#running)
* [TESTS](#tests)
* [VARIÁVEIS DE AMBIENTE](#variaveis-de-ambiente)
* [GUIA DE COMANDOS](#guia-de-comandos)

# DESCRIPTION 
[goto index](#index)

This project started as a learning process for a VSCODE extension called [`PlatformIO IDE`](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide).

The biggest incentive was to migrate from Arduino IDE to a more robust code editor. 

## THE CODE SO FAR 
[goto index](#index)

The codes found here are just pieces that I wrote for my personal projects and felt like it could be useful later.

Most of it may or may not be bad examples. They work for my purposes and are all results of a good amount of time spent learning C++ and it's compilers.

There are `dynamic allocations` and I am trying to write all of it following the `S.O.L.I.D.` principles. I do know that many developers are against use of OOP for embeeded microchips, but the code does not aim to be the final form of anything. And I made a non OOP example with ease just by copying and pasting the OOP ones, so everything here can be used for prototyping.

To run, you must have at least one Arduino UNO and all components models declared in `main.cpp`. As this repository grows, many new components will be added and later surely it will need some reorganizing.
If you know how those components works, you can build the circuit by yourself.

Pins are always defined inside the `example class` for the simplicity of readability.

Examples are instantiated into the `main.c` file.

Since this project does not target a specific project/purpose, many examples can be built, so the `main.cpp` will be constantly modified to adequate the most recent examples, or the ones I use the most.


## EMOJIS 
[goto index](#index)

[Lista de emojis](https://emojis.github.io/index.html)
