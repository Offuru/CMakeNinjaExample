# CMakeNinjaExample

This is repo serves as an example for how to compile a small dll using Ninja and GCC.

## Requirements

1. Ninja
It's a lightweight build system that focuses on speed

Releases: https://github.com/ninja-build/ninja/releases

How to install:

Download the zip that corresponds to your OS, unzip to desired directory (eg. "C:/Users/YourUser/.ninja")
Add the directory to the path variable
On Windows: 
Open searchbar -> Edit the system environment variables -> Environment Variables... -> Double click 'Path' -> New -> Add your path
Note: add the path to the parent directory of ninja.exe, not to ninja.exe itself (eg. "C:/Users/YourUser/.ninja", not "C:/Users/YourUser/.ninja/ninja.exe")

2. GCC Compiler
Install MSys2 (collection of tools and libraries for Windows, Linux should have g++ and gcc builtin) 

How to install:
Follow the instructions at https://www.msys2.org
Add ucrt64/bin to the path variable (eg. "C:/msys64/ucrt64/bin") 
Now you should have access to g++ (C++ compiler) and cc (C compiler) in the command line
Running 'g++ --version' and 'cc --version' in the cmd should yield compiler information

3. CMake
Tool for making compiling C/C++ apps much more user friendly

How to install:
Follow the instructions in the handout for the first Spring School session

## Project structure

1. source/dll: source files for the dll we want to compile
    - source/dll/include: contains the header files of our dll (other c++ apps that want to use the dll will need access to this directory)
    - source/dll/src: contains the source files that will be compiled in a dll

2. source/app
    - source/app/src: contains the source files for the app we are building (it will use functionality from the dll)