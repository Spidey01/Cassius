# INSTALL

## Quick Install

    cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/usr/local
    cmake --build build --target install

CMake defaults CMAKE\_INSTALL\_PREFIX to sane values for most platforms.

If the installed version of cmake is too old for the -S and -B options then it
is highly recommended that you first update cmake.

## Packages

    cmake --build build --target package

To control what format package(s) are created: set CPACK\_BINARY\_\<GEN\> for
the CPACK\_GENERATORs you want to enable or disable. CMake's defaults depend on
the host environment.

## CMake Presets

A recent version of CMake is required to use presets.

    cmake --list-presets
    Available configure presets:

    "Linux"   - Linux Development
    "Windows" - Windows Development
    "Package" - Create Packages

    cmake --preset Windows
    cmake --build --preset Windows

Read CMakePresets.json for more details on individual presets.  These configure
presets expect to VCPKG\_ROOT to be set before runing cmake.

## Using vcpkg

Set VCPKG\_ROOT before running cmake.

### Setup

    git clone  https://github.com/microsoft/vcpkg.git

    .\vcpkg\bootstrap-vcpkg.sh
    export VCPKG_ROOT=${PWD}/vcpkg

    OR

    .\vcpkg\bootstrap-vcpkg.bat
    SET VCPKG_ROOT=%CD%\vcpkg

### Configuration

Since manifest mode is used once VCPKG_ROOT is setup: the rest is taken care of
by the toolchain file.  Configure cmake using CMAKE\_TOOLCHAIN\_FILE when
configuring or use a CMake Preset.

    cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake

    OR

    cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake

When ENABLE_REDIST=ON (default), the install and package targets will include
the dependencies from VCPKG_ROOT. Be aware of that if you are disabling
VCPKG_MANIFEST_MODE and using a large VCPKG_ROOT shared by multiple projects.
