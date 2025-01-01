# EasyUI

A lightweight and easy-to-use GUI library for C applications, designed to be easily integrated into any project.

## Features

- Native Windows window creation and management
- Modern drawing API with styles and shapes
- Event-driven architecture
- Simple and clean API
- Lightweight and minimal dependencies
- Easy integration with existing projects

## Installation

### Windows

#### Quick Install (Recommended)
1. Download the latest release
2. Run `install_windows.bat` as administrator
3. That's it! The script will:
   - Detect your installed compilers (MinGW/MSVC)
   - Build the library
   - Install headers and libraries
   - Set up system PATH
   - Create pkg-config files

#### Manual Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/easyui.git
   cd easyui
   ```

2. Build the library:
   ```bash
   # For MinGW
   scripts/build_mingw.bat

   # For Visual Studio (run from Developer Command Prompt)
   scripts/build_windows_libs.bat
   ```

3. Copy files to your project:
   - Copy `include/easyui.h` to your project's include directory
   - Copy `libs/mingw/libeasyui.a` or `libs/msvc/easyui.lib` to your project's lib directory

## Using EasyUI in Your Project

### With MinGW
```bash
# Single file
gcc your_program.c -I"C:/Program Files/EasyUI/include" -L"C:/Program Files/EasyUI/lib" -leasyui -lgdi32 -luser32 -o your_program

# With pkg-config
gcc your_program.c `pkg-config --cflags --libs easyui` -o your_program
```

### With Visual Studio
```bash
# Command line
cl your_program.c /I"C:/Program Files/EasyUI/include" /link "C:/Program Files/EasyUI/lib/easyui.lib" gdi32.lib user32.lib

# In Visual Studio project:
# 1. Add "C:/Program Files/EasyUI/include" to Include Directories
# 2. Add "C:/Program Files/EasyUI/lib" to Library Directories
# 3. Add "easyui.lib;gdi32.lib;user32.lib" to Additional Dependencies
```

### With CMake
```cmake
# In your CMakeLists.txt
find_package(EasyUI REQUIRED)
target_link_libraries(your_project PRIVATE EasyUI::easyui)
```

## Basic Usage

### 1. Create a Simple Window
```c
#include <easyui.h>

int main() {
    // Create and show a window
    EUI_Window* window = EUI_CreateWindow("Hello EasyUI", 100, 100, 800, 600);
    if (!window) return 1;
    
    EUI_ShowWindow(window);
    EUI_ProcessMessages();
    return 0;
}
```

### 2. Add Event Handlers
```c
void onPaint(EUI_Window* window) {
    // Draw text
    EUI_TextStyle style = EUI_DEFAULT_TEXT_STYLE;
    style.fontSize = 24;
    style.color = RGB(0, 0, 0);
    EUI_DrawTextEx(window, "Hello, EasyUI!", 10, 10, &style);
    
    // Draw shapes
    EUI_ShapeStyle shapeStyle = EUI_DEFAULT_SHAPE_STYLE;
    shapeStyle.fillColor = RGB(200, 200, 255);
    shapeStyle.borderColor = RGB(0, 0, 255);
    EUI_DrawRectangleEx(window, 10, 50, 200, 100, &shapeStyle);
}

void onClick(EUI_Window* window, EUI_Point point) {
    printf("Clicked at (%d, %d)\n", point.x, point.y);
}

int main() {
    EUI_Window* window = EUI_CreateWindow("Hello EasyUI", 100, 100, 800, 600);
    if (!window) return 1;
    
    // Set event handlers
    window->onPaint = onPaint;
    window->onClick = onClick;
    
    EUI_ShowWindow(window);
    EUI_ProcessMessages();
    return 0;
}
```

## Examples

Check out the `examples` directory for more examples:
- `calculator.c` - A fully functional calculator
- `shapes.c` - Demonstrates drawing shapes and handling mouse events
- More examples coming soon!

## Building the Examples

### With MinGW
```bash
cd examples
gcc calculator.c -I"C:/Program Files/EasyUI/include" -L"C:/Program Files/EasyUI/lib" -leasyui -lgdi32 -luser32 -o calculator
```

### With Visual Studio
```bash
cd examples
cl calculator.c /I"C:/Program Files/EasyUI/include" /link "C:/Program Files/EasyUI/lib/easyui.lib" gdi32.lib user32.lib
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.
