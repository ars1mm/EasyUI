# EasyUI Linking Guide

This directory contains comprehensive documentation on how to link EasyUI with your project using different methods.

## Available Linking Methods

1. [CMake Integration](cmake.md)
   - Modern, cross-platform build system
   - Recommended for new projects
   - Best for large, complex projects

2. [pkg-config](pkg-config.md)
   - Standard Unix-like systems integration
   - Easy command-line usage
   - Great for Makefile projects

3. [Visual Studio](visual-studio.md)
   - Native Windows development
   - Full IDE integration
   - Best for Windows-only projects

4. [Direct Linking](direct.md)
   - Manual compilation and linking
   - No build system required
   - Good for learning and simple projects

## Choosing a Linking Method

### Use CMake if:
- You need cross-platform compatibility
- Your project is large or complex
- You want modern dependency management

### Use pkg-config if:
- You're on a Unix-like system
- You use Makefiles
- You want simple command-line integration

### Use Visual Studio if:
- You're developing exclusively for Windows
- You prefer IDE integration
- You want native Windows tooling

### Use Direct Linking if:
- You have a simple project
- You want to understand the linking process
- You don't need a build system

## General Tips

1. **Installation Location**
   - Standard: `/usr/local` (Unix) or `C:\Program Files\EasyUI` (Windows)
   - Custom: Set appropriate environment variables

2. **Required Libraries**
   - EasyUI: `-leasyui`
   - Windows: `-lgdi32 -luser32`

3. **Environment Variables**
   - `EASYUI_ROOT`: Installation directory
   - `PATH`: For runtime library loading
   - Build system specific variables

4. **Common Issues**
   - Header not found: Check include paths
   - Library not found: Check library paths
   - Runtime errors: Check DLL/SO paths

## Example Projects

Find complete example projects in the `examples` directory:
- CMake example
- Visual Studio solution
- Makefile project
- Simple direct linking
