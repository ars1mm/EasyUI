@echo off
echo Building EasyUI library...

:: Set compiler flags
set CFLAGS=-Wall -O2 -I./include
set LDFLAGS=-lgdi32 -luser32 -lm

:: Create directories if they don't exist
if not exist libs mkdir libs
if not exist "libs\mingw" mkdir "libs\mingw"
if not exist "libs\mingw\obj" mkdir "libs\mingw\obj"
if not exist "libs\mingw\obj\styles" mkdir "libs\mingw\obj\styles"
if not exist "libs\mingw\obj\window" mkdir "libs\mingw\obj\window"
if not exist "libs\mingw\obj\graphics" mkdir "libs\mingw\obj\graphics"

:: Clean old files
del /Q "libs\mingw\obj\styles\*.o" 2>nul
del /Q "libs\mingw\obj\window\*.o" 2>nul
del /Q "libs\mingw\obj\graphics\*.o" 2>nul
del /Q "libs\mingw\*.a" 2>nul
del /Q "examples\*.exe" 2>nul

echo.
echo Compiling library components...

:: Compile each component
gcc %CFLAGS% -c "src/styles/styles.c" -o "libs/mingw/obj/styles/styles.o"
if errorlevel 1 goto error

gcc %CFLAGS% -c "src/window/window.c" -o "libs/mingw/obj/window/window.o"
if errorlevel 1 goto error

gcc %CFLAGS% -c "src/graphics/graphics.c" -o "libs/mingw/obj/graphics/graphics.o"
if errorlevel 1 goto error

echo.
echo Creating static library...

:: Create static library
ar rcs "libs/mingw/libeasyui.a" ^
    "libs/mingw/obj/styles/styles.o" ^
    "libs/mingw/obj/window/window.o" ^
    "libs/mingw/obj/graphics/graphics.o"
if errorlevel 1 goto error

echo.
echo Building examples...

:: Compile examples
gcc %CFLAGS% -o "examples/calculator.exe" "examples/calculator.c" -L./libs/mingw -leasyui %LDFLAGS%
if errorlevel 1 goto error

gcc %CFLAGS% -o "examples/shapes.exe" "examples/shapes.c" -L./libs/mingw -leasyui %LDFLAGS%
if errorlevel 1 goto error

echo.
echo Build completed successfully!
goto end

:error
echo.
echo Build failed with error %errorlevel%
exit /b %errorlevel%

:end
