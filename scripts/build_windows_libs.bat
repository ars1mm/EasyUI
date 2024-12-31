@echo off
setlocal enabledelayedexpansion

:: Check if Visual Studio is installed and set up environment
where cl >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo Visual Studio not found in PATH
    echo Please run this script from a Visual Studio Developer Command Prompt
    exit /b 1
)

:: Create directories if they don't exist
if not exist build\lib mkdir build\lib
if not exist build\bin mkdir build\bin

:: Compile static library
echo Building static library (easyui.lib)...
cl /c /MD /O2 /GL /I"include" src\easyui.c /Fo"build\easyui.obj"
lib /OUT:"build\lib\easyui.lib" "build\easyui.obj"

:: Compile dynamic library
echo Building dynamic library (easyui.dll)...
cl /LD /MD /O2 /GL /I"include" src\easyui.c /Fe"build\bin\easyui.dll" /Fo"build\easyui_dll.obj" user32.lib gdi32.lib /link /DLL

:: Clean up object files
del build\*.obj

echo.
echo Build complete!
echo Static library: build\lib\easyui.lib
echo Dynamic library: build\bin\easyui.dll

:: Copy headers to build directory
if not exist build\include mkdir build\include
copy include\easyui.h build\include\

echo.
echo Files have been built and copied to the build directory.
echo You can now copy the contents of the build directory to your desired installation location.
