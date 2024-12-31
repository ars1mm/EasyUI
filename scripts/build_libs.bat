@echo off
setlocal enabledelayedexpansion

:: Check if Visual Studio is installed and set up environment
where cl >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo Visual Studio not found in PATH
    echo Please run this script from a Visual Studio Developer Command Prompt
    exit /b 1
)

:: Set directories
set "LIBS_DIR=libs"
set "STATIC_DIR=%LIBS_DIR%\static"
set "DYNAMIC_DIR=%LIBS_DIR%\dynamic"
set "DEBUG_DIR=%LIBS_DIR%\debug"

:: Create directories
if not exist %STATIC_DIR% mkdir %STATIC_DIR%
if not exist %DYNAMIC_DIR% mkdir %DYNAMIC_DIR%
if not exist %DEBUG_DIR% mkdir %DEBUG_DIR%

:: Build Release Static Library
echo Building Release Static Library (easyui.lib)...
cl /c /MD /O2 /GL /I"include" src\easyui.c /Fo"%STATIC_DIR%\easyui.obj"
lib /OUT:"%STATIC_DIR%\easyui.lib" "%STATIC_DIR%\easyui.obj"
del "%STATIC_DIR%\easyui.obj"

:: Build Release Dynamic Library
echo Building Release Dynamic Library (easyui.dll)...
cl /LD /MD /O2 /GL /I"include" src\easyui.c /Fe"%DYNAMIC_DIR%\easyui.dll" /Fo"%DYNAMIC_DIR%\easyui_dll.obj" user32.lib gdi32.lib /link /DLL
del "%DYNAMIC_DIR%\easyui_dll.obj"
if exist "%DYNAMIC_DIR%\easyui.lib" move "%DYNAMIC_DIR%\easyui.lib" "%DYNAMIC_DIR%\easyui_dll.lib"
if exist "%DYNAMIC_DIR%\easyui.exp" del "%DYNAMIC_DIR%\easyui.exp"

:: Build Debug Static Library
echo Building Debug Static Library (easyuid.lib)...
cl /c /MDd /Od /Zi /I"include" src\easyui.c /Fo"%DEBUG_DIR%\easyuid.obj"
lib /OUT:"%DEBUG_DIR%\easyuid.lib" "%DEBUG_DIR%\easyuid.obj"
del "%DEBUG_DIR%\easyuid.obj"

:: Build Debug Dynamic Library
echo Building Debug Dynamic Library (easyuid.dll)...
cl /LD /MDd /Od /Zi /I"include" src\easyui.c /Fe"%DEBUG_DIR%\easyuid.dll" /Fo"%DEBUG_DIR%\easyuid_dll.obj" user32.lib gdi32.lib /link /DLL
del "%DEBUG_DIR%\easyuid_dll.obj"
if exist "%DEBUG_DIR%\easyuid.lib" move "%DEBUG_DIR%\easyuid.lib" "%DEBUG_DIR%\easyuid_dll.lib"
if exist "%DEBUG_DIR%\easyuid.exp" del "%DEBUG_DIR%\easyuid.exp"

:: Copy header to libs directory
copy "include\easyui.h" "%LIBS_DIR%\"

echo.
echo Build complete! Libraries created in the %LIBS_DIR% directory:
echo.
echo Static Libraries:
echo   %STATIC_DIR%\easyui.lib  (Release)
echo   %DEBUG_DIR%\easyuid.lib  (Debug)
echo.
echo Dynamic Libraries:
echo   %DYNAMIC_DIR%\easyui.dll     (Release)
echo   %DYNAMIC_DIR%\easyui_dll.lib (Release import library)
echo   %DEBUG_DIR%\easyuid.dll      (Debug)
echo   %DEBUG_DIR%\easyuid_dll.lib  (Debug import library)
echo.
echo Header File:
echo   %LIBS_DIR%\easyui.h
