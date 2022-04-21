# Windows Build Notes (on Windows and Ubuntu 16.04, x64)

Building Iridium for Windows requires working with two separate development environments:

-   Visual Studio 2017 on Native Windows (for building Google's V8 JavaScript engine and a V8 service DLL for Iridium)
-   GCC MinGW cross compiler on Linux (for building the Iridium project)

In different stages of the build, artifacts from one environment need to be available to the other environment. If possible, sharing a single physical file system is most helpful. Otherwise, files need to be copied between the two file systems (e.g. *scp* on Linux, *pscp* from Putty or WinSCP on Windows).

The ideal system combination is WSL (Windows Subsystem for Linux) on Windows 10 (Creator edition or later). Search for "Ubuntu" in the Microsoft Store.

The reminder of these instructions assumes that the the environment variable `IRIDIUM_HOME` is the root folder of Iridium. Variables on Windows are referenced by `%VAR%`, and on Linux by `$VAR` or `${VAR}`.

## Prerequisites on Windows

-   [Visual Studio 2017](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=15) (community edition acceptable)
-   [Python 2.7](https://www.python.org/ftp/python/2.7.15/python-2.7.15.amd64.msi)
-   [Git](https://github.com/git-for-windows/git/releases/download/v2.19.1.windows.1/Git-2.19.1-64-bit.exe)
-   [CMake](https://github.com/Kitware/CMake/releases/download/v3.13.1/cmake-3.13.1-win64-x64.msi)
-   [Boost 1.65.1](https://sourceforge.net/projects/boost/files/boost-binaries/1.65.1/boost_1_65_1-msvc-14.1-64.exe/download)

## Prerequisites on Linux

        sudo apt update
        sudo apt install -y libtool autotools-dev automake pkg-config git python python-pip nasm
        sudo apt install -y g++-mingw-w64-x86-64 mingw-w64-x86-64-dev
        sudo pip install pathlib2

## Build Instructions

**Note**: *If sources on the Windows system are accessible from Linux, you can ignore the stage "Prepare a build area on the Linux machine"*.

### Prepare a build area on the *Linux* machine

On Linux:

-   In the location where you want to build Iridium:

        git clone https://github.com/hiridium/iridium.git
        cd iridium
        export IRIDIUM_HOME=$(pwd)

### Prepare a build area on the *Windows* machine

On Windows:

-   In the location where you want to build Iridium:

        git clone https://github.com/hiridium/iridium.git
        cd iridium
        set IRIDIUM_HOME=%CD%

### Prepare to download or build V8

On Windows:

        cd %IRIDIUM_HOME%
        mkdir v8build
        cd v8build

    
You can use pre-built headers and binaries of Google's V8 JavaScript engine by downloading and expanding [windows-v8.zip](https://github.com/hiridium/v8/releases/download/v8/windows-v8.zip) in the current directory.

If, on the other hand, you prefer to build the V8 component yourself, please perform the following:

-   Follow the instructions in [V8_win.md](V8_win.md) to fetch, configure and build Google's V8 JavaScript engine.

-   To facilitate building an additional library required by Iridium, copy the following files to the Linux machine, in the same relative folder:

        %IRIDIUM_HOME%\v8build\v8\out.gn\x64.release\*.bin -> $IRIDIUM_HOME/v8build/v8/out.gn/x64.release
        %IRIDIUM_HOME%\v8build\v8\out.gn\x64.release\*.dat -> $IRIDIUM_HOME/v8build/v8/out.gn/x64.release

On Linux:

        export RELEASE_HOME=$IRIDIUM_HOME/v8build/v8/out.gn/x64.release
        cd $RELEASE
        mkdir obj
        python $IRIDIUM_HOME/depends/v8_data_lib.py -m $IRIDIUM_HOME -o win32

-   Copy `obj/v8_data.lib` to `%IRIDIUM_HOME%\v8build\v8\out.gn\x64.release\obj` on Windows.

On Windows:

            cd %IRIDIUM_HOME%\src\v8_win
            mkdir build
            cd build
            cmake -G "Visual Studio 15 2017 Win64" ..
            
-   If CMake cannot find your Boost installation, try the following command, replacing the location of Boost if it is installed somewhere else:

            cmake -DBOOST_ROOT=C:\local\boost_1_65_1 -G "Visual Studio 15 2017 Win64" ..
            
-   Build the Iridium V8 service DLL

            cmake --build . --config Release --target spdlog
            cmake --build . --config Release


-   Copy `%IRIDIUM_HOME%\src\v8_win\build\Release\iridium_v8.lib` to `$IRIDIUM_HOME/src/v8_win/build/Release` on Linux.
-   Copy `%IRIDIUM_HOME%\src\v8_win\build\Release\iridium_v8.dll` to `%IRIDIUM_HOME%\src` (on local Windows).

### Build Iridium and test that it is alive

On Linux:

        cd $IRIDIUM_HOME
        ./autogen.sh
        cd depends
        make HOST=x86_64-w64-mingw32
        cd ..
        ./configure --prefix=$(pwd)/depends/x86_64-w64-mingw32 --enable-cxx --disable-shared --enable-static --with-pic
        make

-   This will build `iridiumd.exe`, `iridium-cli.exe` and `iridium-util.exe` in the `src` directory[<sup>1</sup>](#f1).
-   Copy `src/iridiumd.exe`, `src/iridium-cli.exe` and `src/iridium-util.exe` to `%IRIDIUM_HOME%\src` on Windows.

On Windows:

        cd %IRIDIUM_HOME%
        src\iridiumd.exe --help

-   If all went well, you should see the expected help text from the program.

Notes:

<a class="anchor" id="f1"></a>1. If you have more than one CPU on your machine, you can speed things up using the `-j#` flag on the last `make` command.
