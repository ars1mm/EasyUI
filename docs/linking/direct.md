# Direct Linking with EasyUI

This guide explains how to manually link EasyUI in your project without using build systems.

## Prerequisites

- GCC, Clang, or compatible C compiler
- EasyUI installed on your system

## Basic Compilation

### Windows (MinGW)

```bash
gcc -I/usr/local/include your_program.c -L/usr/local/lib -leasyui -lgdi32 -luser32 -o your_program
```

### Windows (MSVC)

```bash
cl /I"C:\Program Files\EasyUI\include" your_program.c /link /LIBPATH:"C:\Program Files\EasyUI\lib" easyui.lib gdi32.lib user32.lib
```

## Detailed Compilation Options

### Include Paths (-I)

Tell the compiler where to find headers:
```bash
-I/usr/local/include          # Standard installation
-I/custom/path/include        # Custom installation
-I../include                  # Relative path
```

### Library Paths (-L)

Tell the linker where to find libraries:
```bash
-L/usr/local/lib             # Standard installation
-L/custom/path/lib           # Custom installation
-L../lib                     # Relative path
```

### Libraries (-l)

Link required libraries:
```bash
-leasyui                     # EasyUI library
-lgdi32                      # Windows GDI
-luser32                     # Windows User Interface
```

## Example Shell Script (build.sh)

```bash
#!/bin/bash

# Configuration
CC=gcc
INCLUDES="-I/usr/local/include"
LIBDIRS="-L/usr/local/lib"
LIBS="-leasyui -lgdi32 -luser32"
CFLAGS="-Wall -Wextra -O2"

# Compile
$CC $INCLUDES $LIBDIRS $CFLAGS your_program.c $LIBS -o your_program
```

## Example Batch Script (build.bat)

```batch
@echo off
SET CC=gcc
SET INCLUDES=-I"C:\Program Files\EasyUI\include"
SET LIBDIRS=-L"C:\Program Files\EasyUI\lib"
SET LIBS=-leasyui -lgdi32 -luser32
SET CFLAGS=-Wall -Wextra -O2

%CC% %INCLUDES% %LIBDIRS% %CFLAGS% your_program.c %LIBS% -o your_program.exe
```

## Environment Setup

### Windows

Add these to your system environment variables:
```
EASYUI_INCLUDE=C:\Program Files\EasyUI\include
EASYUI_LIB=C:\Program Files\EasyUI\lib
PATH=%PATH%;C:\Program Files\EasyUI\bin
```

## Project Structure Example

```
your_project/
├── src/
│   ├── main.c
│   └── window.c
├── include/
│   └── window.h
├── build.sh
└── build.bat
```

## Troubleshooting

### Common Issues

1. **Header Not Found**
   ```
   fatal error: easyui.h: No such file or directory
   ```
   Solution: Check include path (-I option)

2. **Library Not Found**
   ```
   undefined reference to `EUI_CreateWindow'
   ```
   Solution: Check library path (-L option) and library name (-l option)

3. **DLL Not Found**
   ```
   The program can't start because easyui.dll is missing
   ```
   Solution: Add EasyUI's bin directory to PATH

### Debug Build

Add these flags for debugging:
```bash
gcc -g -O0 -I/usr/local/include your_program.c -L/usr/local/lib -leasyui -lgdi32 -luser32 -o your_program
```

### Release Build

Add these flags for release:
```bash
gcc -O2 -DNDEBUG -I/usr/local/include your_program.c -L/usr/local/lib -leasyui -lgdi32 -luser32 -o your_program
```

## Distribution

When distributing your application:
1. Include all necessary DLLs
2. Document required system dependencies
3. Provide build instructions

## Best Practices

1. Use consistent paths across your project
2. Document compilation commands
3. Create build scripts for convenience
4. Include debug and release configurations
5. Test on different compiler versions
