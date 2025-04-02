# CMakeNinjaExample

This is repo serves as an example for how to compile a small dll using Ninja and GCC.

## Requirements

#### Ninja
It's a lightweight build system that focuses on speed

Releases: https://github.com/ninja-build/ninja/releases

How to install:

Download the zip that corresponds to your OS, unzip to desired directory (eg. "C:/Users/YourUser/.ninja")  
Add the directory to the path variable  
On Windows:   
Open searchbar -> Edit the system environment variables -> Environment Variables... -> Double click 'Path' -> New -> Add your path  
Note: add the path to the parent directory of ninja.exe, not to ninja.exe itself (eg. "C:/Users/YourUser/.ninja", not "C:/Users/YourUser/.ninja/ninja.exe")

#### GCC Compiler
Install MSys2 (collection of tools and libraries for Windows, Linux should have g++ and gcc builtin)  

How to install:  
Follow the instructions at https://www.msys2.org  
Add ucrt64/bin to the path variable (eg. "C:/msys64/ucrt64/bin")   
Now you should have access to g++ (C++ compiler) and cc (C compiler) in the command line  
Running 'g++ --version' and 'cc --version' in the cmd should yield compiler information  

#### CMake
Tool for making compiling C/C++ apps much more user friendly

How to install:
Follow the instructions in the handout for the first Spring School session

## Project structure

#### source/dll:
    - source/dll/include: contains the header files of our dll (other c++ apps that want to use the dll will need access to this directory)s
    - source/dll/src: contains the source files that will be compiled in a dll

#### source/app

    - source/app/src: contains the source files for the app we are building (it will use functionality from the dll)

## Compiling the dll and app

#### DLL

Before running make sure you are in the source/dll directory

Create a build directory, this is where code is compiled to
```cmd
mkdir build
cd build
```

Run CMake and set the generator to Ninja, the C++ compiler path macro to g++, the C compiler path macro to cc and specify the location of `CMakeLists.txt` (in our case the parent directory). Note that we can write g++ and cc directly because we added ucrt64/bin to the path variable, so the system has access to `g++.exe` and `cc.exe`

```cmd
cmake -G "Ninja" -D CMAKE_CXX_COMPILER=g++  -D CMAKE_C_COMPILER=cc -D ..
```

This generates the files that Ninja needs to compile our dll as well as a `kits` directory we specified in `CMakeLists.txt`. We can now build the dll by running

```cmd
ninja
```

Notice this generated a directory `1.0.0` containing our dll. That is because if the variable `DLL_VERSION` isn't defined then it is automatically set to the string "1.0.0". We can instead specify the value of `DLL_VERSION` the same way we did for the C and C+= compilers

```cmd
cmake -G "Ninja" -D CMAKE_CXX_COMPILER=g++  -D CMAKE_C_COMPILER=cc -D DLL_VERSION=1.0.1 ..
```

Building the dll now will instead create a `1.0.1` directory containing a different version of our dll

Now that we built our dlls we can build the main app, by running the same commands as we did for the first version of our dll (the paths to the include and dll directories have already been set in `source/app/CMakeLists.txt`).
Before running these commands again make sure you're in the `source/app` directory, not `source/dll`
```cmd
mkdir build
cd build
```
```cmd
cmake -G "Ninja" -D CMAKE_CXX_COMPILER=g++  -D CMAKE_C_COMPILER=cc -D ..
```
```cmd
ninja
```

Our app has now been compiled into `my_app.exe`, running
```cmd
./my_app.exe
```
should print our dll version.

Just as we did with our dll compilation, we can specify the value of the variable `DLL_VERSION` that `app/CMakeLists.txt` uses (notice that we declare a default value for `DLL_VERSION` if one isn't provided the same way we did for the dll)

```cmd
cmake -G "Ninja" -D CMAKE_CXX_COMPILER=g++  -D CMAKE_C_COMPILER=cc -D DLL_VERSION=1.0.0 ..
```

General DLL notions:

Most 3rd party tools (for example GUI libraries) will provide prebuilt binaries (`.dll` and `.lib` or `.a` files that the user can link to directly) as well as the source code (in case the user wants customize the library compilation for they use).  
In order to use different libraries in your code the compiler will need to know where to find them and how to use them. Libraries are usually provided as zip folders containing 3 or 4 main directories, `include`, `lib`, `bin` and `src` (if the source code is provided).  
The `include` directory contains the header files you will include in your application and they serve as templates (think of interfaces in OOP languages) for the dll structure (eg. it let's our compiler know what classes and methods we have available). If we only provide the include file the method and class definitons will be recognized by our program but we will get a linking error when trying to call the method, since a header file should normally only contain the class definitions and method headers, not the implementation itself.  
The `lib` directory contains `.lib` files which are called "import libraries" that are used to link to the DLL. They provide additional information regarding methods and variables in the dll and act as a bridge between our application and the dll we are trying to use.
Finally, the `bin` directory contains the actual dll files which the application usually requires at runtime in order to use the implementations of the methods and classes defined in the header and lib files.

In this example, all the paths have been predefined and as such you don't need to bother with organizing the files. In real projects you will usually have a `libraries` directory containing the `include` and `lib` directories for the libraries you are trying to use (whether you group all the includes/libs for different libraries into one directory or use one directory with a `include` and `lib` per library used is up to you). The dll files are usually put in the same directory as the `.exe` itself so that they can be found at runtime.

Most IDEs (eg. Visual Studio) offer GUIs that greatly simplify the process of linking libraries but under the hood they set the variables in a similar way to the one we used to compile this project.