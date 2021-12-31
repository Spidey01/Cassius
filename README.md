# README

Cassius is C++ library designed to easily embed scripting languages in programs.

Cassius provides the same general API for each script engine, allowing programs to support several different backends or chose the language of choice. Of course, if you load a Python back end and try feeding it Lua code, that's your problem :-P.

## Building Instructions

    mkdir build
    cd build
    cmake /path/to/source
    cmake --build .

To run the test suite after a build:

    cmake --build . --target test

## Packaging and Installation

The "install" target can be used to install the build into the CMAKE_INSTALL_PREFIX.

The "package" target can be used to package the build for redistribution.

Configure the build with CPACK_BINARY_<GEN> set to enable or disable specific package formats.  E.g.

    cmake -DCPACK_BINARY_ZIP=ON -DCPACK_BINARY_NSIS=OFF /path/to/source

Look in the CMakeCache.txt to see what CMake auto detected for your environment.

## General Dependencies

### C++ Compiler

Development uses recent GNU and Microsoft compilers. A not too ancient version of either should work but may not be tested.

### CMake

While most files set cmake_minimum_required() to 3.0: only far more recent versions are actually tested! Some features may require a newer version of CMake. Such as a Find{Dep} module that doesn't support specific versions of {Dep} before CMake 3.XY.

### Deps/cxx-plugin

A submodule of [cxx-plugin](http://github.com/Spidey01/cxx-plugin) is used for loading the language backends at run time. The build system expects to find this in Deps/cxx-plugin. When building from git just populate the submodule.

    git submodule init
    git submodule update

## Specific Dependencies

These are only needed if you wish to build the relevant components of Cassius. When found support is enabled automatically. ENABLE_<LANG> can be used to disable looking for <LANG> support.

### Lua Support

[Lua](http://www.lua.org/) support requires a minimum of version 5.1. Cassius can compile against newer versions (e.g. Lua 5.4) and is tested with a contemporary version. Refer to Lua's reference manual for language compatibility issues.

CMake's find_package() command and [FindLua](https://cmake.org/cmake/help/latest/module/FindLua.html) module are used to enable Lua support. Configure the build with ENABLE_LUA=OFF to disable looking for Lua support.

### Python support

[Python](http://www.python.org/) support is experimental / WIP. Originally developed against Python 2.x on FreeBSD. It was barely implemented and only supported unix targets.

CMake's find_package() command and [FindPython](https://cmake.org/cmake/help/latest/module/FindPython.html) modules are used to enable Python support. Configure the build with ENABLE_PYTHON=OFF to disable looking for Python support.

## Dependencies from package managers

### vcpkg

If using [vcpkg](https://vcpkg.io/) to handle dependencies: export VCPKG_ROOT before running cmake.

If the VCPKG_ROOT environment variable is *NOT* set but a /vcpkg directory exits in the project source: Cassius's build system will set ENV{VCPKG_ROOT} to that.

If the VCPKG_TRIPLET environment variable is not defined: Cassius's build system will attempt to guess. You may wish to export this along with VCPKG_ROOT.

If the VCPKG_ROOT environment variable is set but CMake's CMAKE_TOOLCHAIN_FILE variable is not defined: Cassius's build system will infer this from ENV{VCPKG_ROOT}.

### apt

For Debian / Ubuntu based systems

    sudo apt update
    sudo apt install build-essential cmake liblua5.X-dev python3-dev

Replace 'X' with the version of Lua you wish to use. Modern versions of Debian package each version for side by side installation, e.g. liblua5.1-dev and liblua5.4-dev.

Omitt the '-dev' packages if you want to skip that component.

### Windows

Using vcpkg is the easist way to go. See above.

Using MSYS should work but may not be tested as reguarly.
