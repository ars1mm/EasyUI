@echo off
echo Building EasyUI library...

:: Create directories if they don't exist
if not exist libs\mingw mkdir libs\mingw

:: Compile the library
gcc -c -o libs/mingw/easyui.o src/easyui.c -I./include

:: Create static library
ar rcs libs/mingw/libeasyui.a libs/mingw/easyui.o

:: Compile calculator example
gcc -o examples/calculator.exe examples/calculator.c -I./include -L./libs/mingw -leasyui -lgdi32 -luser32

echo Build complete!
