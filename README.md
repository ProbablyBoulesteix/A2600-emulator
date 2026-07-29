# Atari 2600 Emulator 

## About and motivations

This project is an attempt at building and testing an Atari 2600 console emulator. It is written in C++ (standard C++ 20). I have multiple goals here:
- To prove to myself (and others) that I can design, build, test and hopefully deploy a complex, multi-part C++ project.
- To prove to my (currently fictional) detractors that I am perfectly capable of writing functional, readable code without AI assistance.
- To gain further experience programming in C++ after months of Python/C# experience, both as a bid to preserve that skillset while also attempting to use systems engineering skills I've acquired these past few months for another project (building modular + readable code, dealing with edge cases...)
- To have have a nice, show-offy project on my github, in case anyone ever asks in a bid to discount my CS skills by focusing on my mechanical engineering/robotics background
- Because it's fun!

## A brief technical summary

### CPU Emulation
For the CPU portion, this project uses much of the reference material found here: https://www.masswerk.at/6502/6502_instruction_set.html.

Note that the Atari 2600 uses the 6507, a variant of the NMOS 6502, stripped of BCD capabilities and equipped with a 12bit (4096B) address bus (as opposed to the 6502's 16bit address bus). 

Using a 6502 emulator core, as opposed to a 6507 core (and simply stripping away the unused functionality) is done for expandability and modularity: if this code works, it will hopefully one day be used to design a NES Emulator. 

Check the Wiki for more information.


### Memory system

TBD. Check the Wiki for more information.

### TIA

TBD

### LOADER

TBD

### MISC

TBD

## Requirements
This project uses C++ standard 20 and CMAKE >3.18. Additional dependencies will be noted here as the project advances

## Project State
This project is currently unfinished, but in development. Current work focuses on the CPU and memory aspects of the emulator.