# Using EasyUI with CMake

This guide explains how to use EasyUI in your CMake-based project.

## Prerequisites

- CMake 3.10 or higher
- A C compiler (GCC, MSVC, Clang)
- EasyUI installed on your system

## Basic Integration

### 1. Finding the Package

Add this to your `CMakeLists.txt`:

```cmake
find_package(EasyUI REQUIRED)
```

### 2. Linking with Your Target

```cmake
add_executable(your_app main.c)
target_link_libraries(your_app PRIVATE EasyUI::easyui)
```

## Complete Example

Here's a complete `CMakeLists.txt` example:

```cmake
cmake_minimum_required(VERSION 3.10)
project(YourApp VERSION 1.0.0 LANGUAGES C)

# Find EasyUI package
find_package(EasyUI REQUIRED)

# Create executable
add_executable(your_app
    src/main.c
    src/window.c
)

# Link with EasyUI
target_link_libraries(your_app PRIVATE EasyUI::easyui)

# Set C standard (optional)
set_target_properties(your_app PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
)
```

## Advanced Usage

### Custom EasyUI Location

If EasyUI is installed in a non-standard location:

```cmake
list(APPEND CMAKE_PREFIX_PATH "path/to/easyui")
find_package(EasyUI REQUIRED)
```

### Multiple Targets

```cmake
# Library target
add_library(your_lib
    src/lib.c
)
target_link_libraries(your_lib PRIVATE EasyUI::easyui)

# Executable target
add_executable(your_app
    src/main.c
)
target_link_libraries(your_app PRIVATE your_lib EasyUI::easyui)
```

## Troubleshooting

### Common Issues

1. **Package Not Found**
   ```
   CMake Error: Could not find EasyUI
   ```
   Solution: Set `CMAKE_PREFIX_PATH` to the EasyUI installation directory.

2. **Linking Errors**
   ```
   undefined reference to `EUI_CreateWindow'
   ```
   Solution: Ensure EasyUI is properly installed and linked.

### Environment Variables

You can set these environment variables:
- `EASYUI_ROOT`: Path to EasyUI installation
- `CMAKE_PREFIX_PATH`: Add EasyUI installation path

## Example Project Structure

```
your_project/
├── CMakeLists.txt
├── src/
│   ├── main.c
│   └── window.c
└── include/
    └── window.h
```

## Building Your Project

```bash
mkdir build
cd build
cmake ..
cmake --build .
```
