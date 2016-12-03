[![Stories in Ready](https://badge.waffle.io/Kyle-Larson/Kaleidoscope.png?label=ready&title=Ready)](https://waffle.io/Kyle-Larson/Kaleidoscope)
# Kaleidoscope
3D rendering Engine designed for portability for Emscripten compiler.

## Install
To install Kaleidoscope, you'll need the following tools installed and accessible in your PATH
- CMake
- Emscripten
- MinGW (If you are on Windows)

From there, there are two steps to start using the application natively.
- Clone the repo into your desired development folder, and ...
- run Setup.bat to create the project files in the build folder.  

Once you are satisfied with your native application, all you need to do to deploy to the web via Emscripten is run EMSetup.bat.  Once it is run, your output files will be located under the embuild folder.