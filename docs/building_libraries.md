# Building EasyUI Libraries

This guide explains how to build the EasyUI libraries (static and dynamic) for use in your projects.

## Windows

### Prerequisites

- Visual Studio 2017 or later
- Windows SDK
- Administrator privileges (for installation)

### Building the Libraries

1. Open a "Developer Command Prompt for VS" (search in Start menu)

2. Navigate to the EasyUI directory:
   ```cmd
   cd path\to\EasyUI
   ```

3. Run the build script:
   ```cmd
   scripts\build_windows_libs.bat
   ```

   This will create:
   - `build\lib\easyui.lib` (static library)
   - `build\bin\easyui.dll` (dynamic library)
   - `build\include\easyui.h` (header file)

### Installing the Libraries

1. Right-click `scripts\install_windows.bat` and select "Run as administrator"

   This will:
   - Copy files to `C:\Program Files\EasyUI`
   - Add the bin directory to system PATH
   - Create pkg-config configuration

### Manual Installation

If you prefer to install manually:

1. Copy files to your desired location:
   ```
   your_location/
   ├── bin/
   │   └── easyui.dll
   ├── lib/
   │   └── easyui.lib
   └── include/
       └── easyui.h
   ```

2. Add the following environment variables:
   - Add `your_location\bin` to PATH
   - Set `EASYUI_ROOT` to `your_location`

## Using the Libraries

### In Visual Studio

1. Project Properties → C/C++ → General → Additional Include Directories:
   ```
   C:\Program Files\EasyUI\include
   ```

2. Project Properties → Linker → General → Additional Library Directories:
   ```
   C:\Program Files\EasyUI\lib
   ```

3. Project Properties → Linker → Input → Additional Dependencies:
   ```
   easyui.lib
   ```

### With MinGW

```bash
gcc your_program.c -I"C:\Program Files\EasyUI\include" -L"C:\Program Files\EasyUI\lib" -leasyui -o your_program
```

### With CMake

```cmake
find_package(EasyUI REQUIRED)
target_link_libraries(your_project PRIVATE EasyUI::easyui)
```

## Troubleshooting

### Common Issues

1. **LNK2019: Unresolved External Symbol**
   - Check if easyui.lib is correctly linked
   - Verify library path is correct
   - Ensure you're using the right configuration (Debug/Release)

2. **Cannot find easyui.dll**
   - Ensure bin directory is in PATH
   - Copy easyui.dll to your executable's directory
   - Check if you have the right Visual C++ Redistributable installed

3. **Cannot find easyui.h**
   - Verify include path is correct
   - Check if EASYUI_ROOT is set properly

### Building Different Configurations

For Debug build:
```cmd
scripts\build_windows_libs.bat Debug
```

For Release build:
```cmd
scripts\build_windows_libs.bat Release
```

## Distribution

When distributing your application:

1. Include these files with your executable:
   - easyui.dll
   - Visual C++ Redistributable installer

2. Document the requirements:
   - Windows version
   - Visual C++ Redistributable version
   - Any additional dependencies

## Support

If you encounter issues:
1. Check the troubleshooting section above
2. Look for similar issues in our issue tracker
3. Create a new issue with:
   - Your build environment details
   - Steps to reproduce
   - Error messages
   - Build logs
