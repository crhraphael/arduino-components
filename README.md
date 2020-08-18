# arduino-components
A full code sample with many implementations of electronic components to ease readability and modifications for future changes. Made with C++ OOP with .h-only files 

# DESCRIPTION
This project started as a learning process for a VSCODE extension called [PlatformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide).

The biggest incentive was to migrate from Arduino IDE to a more robust code editor. 

## About the code 

The codes found here are just pieces that I wrote for my personal projects and felt like it could be useful for later.

Most of it may or may not be bad. They work for my purposes and are all results of a good amount of time spent learning C++ and it's compilers.

There are dynamic allocations and I am trying to write all of it following the SOLID principles.

Surely it's not the ideal for embeeded microchips, but the code does not aim to be the final form of anything. It's there merely for prototyping, readability and learning processes.

To run, you must have at least one Arduino UNO and all components models declared in `main.cpp`. As this repository grows, many new components will be added and later surely it will need some reorganizing.
If you know how those components works, you can build the circuit by yourself.

Pins are always defined in `main.cpp` for the simplicity of readability. How they are defined are class-specific, and some have constructor params to override the default values.

Since this project does not target a specific project/purpose, many examples can be built, so the `main.cpp` will be constantly modified to adequate the most recent components, or the ones I use the most.
