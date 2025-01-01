@echo off
setlocal enabledelayedexpansion

echo EasyUI Windows Installation Script
echo ================================
echo.

:: Check if running with admin privileges
net session >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: This script requires administrator privileges.
    echo Please right-click and select "Run as administrator"
    pause
    exit /b 1
)

:: Detect available compilers
set FOUND_COMPILER=0

where cl >nul 2>&1
if %errorlevel% equ 0 (
    set FOUND_COMPILER=1
    echo Found: Microsoft Visual Studio
    set "MSVC_DETECTED=1"
) else (
    set "MSVC_DETECTED=0"
)

where gcc >nul 2>&1
if %errorlevel% equ 0 (
    set FOUND_COMPILER=1
    echo Found: MinGW GCC
    set "MINGW_DETECTED=1"
) else (
    set "MINGW_DETECTED=0"
)

if !FOUND_COMPILER! equ 0 (
    echo Error: No supported compiler found.
    echo Please install MinGW or Visual Studio.
    pause
    exit /b 1
)

:: Build the library
echo.
echo Building EasyUI library...
call scripts\build_libs.bat
if %errorlevel% neq 0 (
    echo Error: Build failed
    pause
    exit /b 1
)

:: Create installation directories
set "INSTALL_ROOT=%ProgramFiles%\EasyUI"
set "INCLUDE_DIR=%INSTALL_ROOT%\include"
set "LIB_DIR=%INSTALL_ROOT%\lib"
set "EXAMPLES_DIR=%INSTALL_ROOT%\examples"

echo.
echo Installing to %INSTALL_ROOT%...

if not exist "%INSTALL_ROOT%" mkdir "%INSTALL_ROOT%"
if not exist "%INCLUDE_DIR%" mkdir "%INCLUDE_DIR%"
if not exist "%LIB_DIR%" mkdir "%LIB_DIR%"
if not exist "%EXAMPLES_DIR%" mkdir "%EXAMPLES_DIR%"

:: Copy header files
echo Copying header files...
xcopy /Y "include\*.h" "%INCLUDE_DIR%\"

:: Copy libraries
echo Copying libraries...
if %MINGW_DETECTED% equ 1 (
    if exist "libs\mingw\libeasyui.a" (
        xcopy /Y "libs\mingw\libeasyui.a" "%LIB_DIR%\"
    )
)
if %MSVC_DETECTED% equ 1 (
    if exist "libs\msvc\easyui.lib" (
        xcopy /Y "libs\msvc\easyui.lib" "%LIB_DIR%\"
    )
)

:: Copy examples
echo Copying examples...
xcopy /Y "examples\*.c" "%EXAMPLES_DIR%\"
xcopy /Y "examples\CMakeLists.txt" "%EXAMPLES_DIR%\"

:: Create a .pc file for pkg-config
echo Creating pkg-config file...
set PC_FILE=%LIB_DIR%\easyui.pc
echo prefix=%INSTALL_ROOT%> "%PC_FILE%"
echo exec_prefix=${prefix}>> "%PC_FILE%"
echo libdir=${exec_prefix}/lib>> "%PC_FILE%"
echo includedir=${prefix}/include>> "%PC_FILE%"
echo.>> "%PC_FILE%"
echo Name: EasyUI>> "%PC_FILE%"
echo Description: A lightweight and easy-to-use GUI library for C>> "%PC_FILE%"
echo Version: 1.0.0>> "%PC_FILE%"
echo Libs: -L${libdir} -leasyui -lgdi32 -luser32>> "%PC_FILE%"
echo Cflags: -I${includedir}>> "%PC_FILE%"

:: Add to system PATH
echo Adding to system PATH...
setx PATH "%PATH%;%INSTALL_ROOT%\lib" /M

echo.
echo Installation complete!
echo.
echo To use EasyUI in your projects:
echo.
echo For MinGW:
echo gcc your_program.c -I"%INCLUDE_DIR%" -L"%LIB_DIR%" -leasyui -lgdi32 -luser32 -o your_program
echo.
echo For Visual Studio:
echo cl your_program.c /I"%INCLUDE_DIR%" /link "%LIB_DIR%\easyui.lib" gdi32.lib user32.lib
echo.
echo Example programs are available in: %EXAMPLES_DIR%
echo.
pause
