@echo off
setlocal enabledelayedexpansion

echo Building EasyUI libraries...
echo.

:: Check for build tools
where cl >nul 2>nul
if %errorlevel% equ 0 (
    echo Found MSVC compiler
    call scripts\build_windows_libs.bat
    if %errorlevel% neq 0 (
        echo MSVC build failed
        exit /b %errorlevel%
    )
) else (
    echo MSVC compiler not found, skipping MSVC build
)

where gcc >nul 2>nul
if %errorlevel% equ 0 (
    echo.
    echo Found MinGW compiler
    call scripts\build_mingw.bat
    if %errorlevel% neq 0 (
        echo MinGW build failed
        exit /b %errorlevel%
    )
) else (
    echo MinGW compiler not found, skipping MinGW build
)

echo.
echo Build process completed.
echo.
echo Available libraries:

:: Check and report MSVC build results
if exist libs\msvc\easyui.lib (
    echo - MSVC static library: libs\msvc\easyui.lib
) else (
    echo - MSVC build not available
)

:: Check and report MinGW build results
if exist libs\mingw\libeasyui.a (
    echo - MinGW static library: libs\mingw\libeasyui.a
) else (
    echo - MinGW build not available
)

echo.
echo To use these libraries:
echo 1. Include the header files from the include directory
echo 2. Link against the appropriate library for your compiler:
echo    - For Visual Studio: Use easyui.lib
echo    - For MinGW: Use libeasyui.a
echo 3. Check the examples directory for usage examples

exit /b 0
