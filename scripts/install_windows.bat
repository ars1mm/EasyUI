@echo off
setlocal enabledelayedexpansion

:: Default installation directory
set "INSTALL_DIR=C:\Program Files\EasyUI"

:: Check for administrative privileges
net session >nul 2>&1
if %errorLevel% neq 0 (
    echo This script requires administrative privileges.
    echo Please run as administrator.
    exit /b 1
)

:: Create installation directories
echo Creating installation directories...
if not exist "%INSTALL_DIR%" mkdir "%INSTALL_DIR%"
if not exist "%INSTALL_DIR%\bin" mkdir "%INSTALL_DIR%\bin"
if not exist "%INSTALL_DIR%\lib" mkdir "%INSTALL_DIR%\lib"
if not exist "%INSTALL_DIR%\include" mkdir "%INSTALL_DIR%\include"

:: Copy files
echo Copying files...
copy "build\bin\easyui.dll" "%INSTALL_DIR%\bin\"
copy "build\lib\easyui.lib" "%INSTALL_DIR%\lib\"
copy "include\easyui.h" "%INSTALL_DIR%\include\"

:: Add to system PATH if not already present
echo Updating system PATH...
for /f "tokens=2*" %%a in ('reg query "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v Path ^| findstr /i "^Path"') do set "CURRENT_PATH=%%b"
echo %CURRENT_PATH% | findstr /i /c:"%INSTALL_DIR%\bin" >nul
if %errorLevel% neq 0 (
    setx /M PATH "%CURRENT_PATH%;%INSTALL_DIR%\bin"
    echo Added to system PATH
) else (
    echo Already in system PATH
)

:: Create pkg-config file
echo Creating pkg-config file...
if not exist "%INSTALL_DIR%\lib\pkgconfig" mkdir "%INSTALL_DIR%\lib\pkgconfig"
(
    echo prefix=%INSTALL_DIR:\=/%
    echo exec_prefix=${prefix}
    echo libdir=${exec_prefix}/lib
    echo includedir=${prefix}/include
    echo.
    echo Name: EasyUI
    echo Description: A lightweight and easy-to-use GUI library for C
    echo Version: 0.1.0
    echo Libs: -L${libdir} -leasyui -lgdi32 -luser32
    echo Cflags: -I${includedir}
) > "%INSTALL_DIR%\lib\pkgconfig\easyui.pc"

echo.
echo Installation complete!
echo.
echo Files installed to:
echo   %INSTALL_DIR%\bin\easyui.dll
echo   %INSTALL_DIR%\lib\easyui.lib
echo   %INSTALL_DIR%\include\easyui.h
echo.
echo Please restart your development environment to ensure the new PATH is recognized.
echo.
echo To use in Visual Studio:
echo 1. Add "%INSTALL_DIR%\include" to your include directories
echo 2. Add "%INSTALL_DIR%\lib" to your library directories
echo 3. Add easyui.lib to your linker input
