# Using EasyUI with Visual Studio

This guide explains how to integrate EasyUI into your Visual Studio projects.

## Prerequisites

- Visual Studio 2017 or later
- EasyUI installed on your system
- Windows SDK

## Project Setup

### 1. Create a New Project

1. Open Visual Studio
2. File → New → Project
3. Select "Windows Desktop Application" or "Empty Project"
4. Name your project and click Create

### 2. Configure Project Properties

Right-click your project in Solution Explorer → Properties

#### Include Directories

1. C/C++ → General → Additional Include Directories
2. Add the EasyUI include path:
   ```
   C:\Program Files\EasyUI\include
   ```
   or
   ```
   $(EASYUI_ROOT)\include
   ```

#### Library Directories

1. Linker → General → Additional Library Directories
2. Add the EasyUI library path:
   ```
   C:\Program Files\EasyUI\lib
   ```
   or
   ```
   $(EASYUI_ROOT)\lib
   ```

#### Dependencies

1. Linker → Input → Additional Dependencies
2. Add:
   ```
   easyui.lib
   gdi32.lib
   user32.lib
   ```

## Example Project

### 1. Main Source File (main.c)

```c
#include <easyui.h>
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                  LPSTR lpCmdLine, int nCmdShow) {
    EUI_Window* window = EUI_CreateWindow("My App", 100, 100, 800, 600);
    if (!window) {
        return 1;
    }

    EUI_ShowWindow(window);
    EUI_ProcessMessages();

    return 0;
}
```

### 2. Resource File (optional, app.rc)

```rc
#include <windows.h>

IDI_ICON1 ICON "app.ico"

VS_VERSION_INFO VERSIONINFO
FILEVERSION     1,0,0,0
PRODUCTVERSION  1,0,0,0
BEGIN
    BLOCK "StringFileInfo"
    BEGIN
        BLOCK "040904E4"
        BEGIN
            VALUE "CompanyName",      "Your Company"
            VALUE "FileDescription",   "Your Application"
            VALUE "FileVersion",       "1.0.0.0"
            VALUE "InternalName",      "YourApp"
            VALUE "ProductName",       "Your Application"
            VALUE "ProductVersion",    "1.0.0.0"
        END
    END
END
```

## Build Configurations

### Debug Configuration

1. Set Properties for Debug:
   - C/C++ → Optimization → Optimization: Disabled (/Od)
   - C/C++ → Code Generation → Runtime Library: Multi-threaded Debug DLL (/MDd)
   - Linker → Debugging → Generate Debug Info: Yes (/DEBUG)

### Release Configuration

1. Set Properties for Release:
   - C/C++ → Optimization → Optimization: Maximum Optimization (/O2)
   - C/C++ → Code Generation → Runtime Library: Multi-threaded DLL (/MD)
   - Linker → Debugging → Generate Debug Info: No

## Environment Variables

Create these environment variables for easier configuration:
- `EASYUI_ROOT`: Points to EasyUI installation directory
- `EASYUI_INCLUDE`: Points to include directory
- `EASYUI_LIB`: Points to library directory

## Project Structure Example

```
YourProject/
├── src/
│   ├── main.c
│   └── window.c
├── include/
│   └── window.h
├── resources/
│   ├── app.rc
│   └── app.ico
└── YourProject.sln
```

## Troubleshooting

### Common Issues

1. **LNK2019: Unresolved External Symbol**
   - Check if library paths are correct
   - Verify all required .lib files are listed
   - Ensure Runtime Library settings match

2. **Cannot Find easyui.h**
   - Verify include path is correct
   - Check if EASYUI_ROOT is set properly

3. **Runtime Error: Cannot find easyui.dll**
   - Add EasyUI's bin directory to PATH
   - Copy easyui.dll to output directory

### Solution: Post-Build Event

Add this post-build event to automatically copy DLLs:
```
xcopy "$(EASYUI_ROOT)\bin\easyui.dll" "$(OutDir)" /y
```

## Distribution

When distributing your application:
1. Include easyui.dll with your executable
2. Include Visual C++ Redistributable
3. Include any additional dependencies

## Using NuGet (Alternative)

If available through NuGet:
1. Right-click project → Manage NuGet Packages
2. Search for "EasyUI"
3. Click Install

## Visual Studio Extensions

Consider installing these helpful extensions:
- "Include Tool": Manages include directories
- "Library Manager": Manages library dependencies
