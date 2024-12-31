# Using EasyUI with pkg-config

This guide explains how to use EasyUI in your project using pkg-config.

## Prerequisites

- pkg-config installed on your system
- GCC or compatible compiler
- EasyUI installed on your system

## Basic Usage

### 1. Compiling a Single File

```bash
gcc your_program.c `pkg-config --cflags --libs easyui` -o your_program
```

### 2. Using in Makefiles

```makefile
CFLAGS += $(shell pkg-config --cflags easyui)
LDFLAGS += $(shell pkg-config --libs easyui)

your_program: your_program.c
    $(CC) $(CFLAGS) $< $(LDFLAGS) -o $@
```

## Complete Makefile Example

```makefile
CC = gcc
CFLAGS = -Wall -Wextra $(shell pkg-config --cflags easyui)
LDFLAGS = $(shell pkg-config --libs easyui)

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)
TARGET = your_program

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS) $(TARGET)
```

## Advanced Usage

### 1. Version Check

Check if EasyUI version is compatible:

```bash
pkg-config --print-requires-version easyui
```

### 2. Custom pkg-config Path

If EasyUI is installed in a non-standard location:

```bash
export PKG_CONFIG_PATH=/path/to/easyui/lib/pkgconfig:$PKG_CONFIG_PATH
```

### 3. Static Linking

To link statically:

```bash
gcc your_program.c `pkg-config --static --cflags --libs easyui` -o your_program
```

## Troubleshooting

### Common Issues

1. **Package Not Found**
   ```
   Package easyui was not found in the pkg-config search path
   ```
   Solution: Set PKG_CONFIG_PATH to include EasyUI's pkgconfig directory.

2. **Version Mismatch**
   ```
   Requested 'easyui >= 1.0' but version of EasyUI is 0.9
   ```
   Solution: Update EasyUI or adjust version requirements.

### Environment Variables

Important environment variables:
- `PKG_CONFIG_PATH`: Paths to search for .pc files
- `PKG_CONFIG_LIBDIR`: Override default library directory
- `PKG_CONFIG_SYSROOT_DIR`: For cross-compilation

## Example Project Structure

```
your_project/
├── Makefile
├── src/
│   ├── main.c
│   └── window.c
└── include/
    └── window.h
```

## Verifying Installation

Check if pkg-config can find EasyUI:

```bash
pkg-config --modversion easyui
pkg-config --cflags easyui
pkg-config --libs easyui
```
