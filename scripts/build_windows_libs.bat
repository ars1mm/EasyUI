@echo off
echo Building EasyUI library for Windows...

:: Check for Visual Studio
where cl >nul 2>nul
if %errorlevel% neq 0 (
    echo Error: Visual Studio compiler ^(cl.exe^) not found.
    echo Please run this script from a Visual Studio Developer Command Prompt.
    exit /b 1
)

:: Set compiler flags
set CFLAGS=/nologo /O2 /W4 /I"include" /MT
set LDFLAGS=gdi32.lib user32.lib

:: Create directories if they don't exist
if not exist libs mkdir libs
if not exist "libs\msvc" mkdir "libs\msvc"
if not exist "libs\msvc\obj" mkdir "libs\msvc\obj"
if not exist "libs\msvc\obj\styles" mkdir "libs\msvc\obj\styles"
if not exist "libs\msvc\obj\window" mkdir "libs\msvc\obj\window"
if not exist "libs\msvc\obj\graphics" mkdir "libs\msvc\obj\graphics"

:: Clean old files
del /Q "libs\msvc\obj\styles\*.obj" 2>nul
del /Q "libs\msvc\obj\window\*.obj" 2>nul
del /Q "libs\msvc\obj\graphics\*.obj" 2>nul
del /Q "libs\msvc\*.lib" 2>nul
del /Q "examples\*.exe" 2>nul

echo.
echo Compiling library components...

:: Compile each component
cl.exe %CFLAGS% /c "src/styles/styles.c" /Fo"libs/msvc/obj/styles/styles.obj"
if errorlevel 1 goto error

cl.exe %CFLAGS% /c "src/window/window.c" /Fo"libs/msvc/obj/window/window.obj"
if errorlevel 1 goto error

cl.exe %CFLAGS% /c "src/graphics/graphics.c" /Fo"libs/msvc/obj/graphics/graphics.obj"
if errorlevel 1 goto error

echo.
echo Creating static library...

:: Create static library
lib.exe /nologo /out:"libs/msvc/easyui.lib" ^
    "libs/msvc/obj/styles/styles.obj" ^
    "libs/msvc/obj/window/window.obj" ^
    "libs/msvc/obj/graphics/graphics.obj"
if errorlevel 1 goto error

echo.
echo Building examples...

:: Compile examples
cl.exe %CFLAGS% "examples/calculator.c" /Fe"examples/calculator.exe" /link /LIBPATH:"libs/msvc" easyui.lib %LDFLAGS%
if errorlevel 1 goto error

cl.exe %CFLAGS% "examples/shapes.c" /Fe"examples/shapes.exe" /link /LIBPATH:"libs/msvc" easyui.lib %LDFLAGS%
if errorlevel 1 goto error

echo.
echo Build completed successfully!
goto end

:error
echo.
echo Build failed with error %errorlevel%
exit /b %errorlevel%

:end
