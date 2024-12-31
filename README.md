# EasyUI

A lightweight and easy-to-use GUI library for C applications, designed to be easily integrated into any project.

## Features

- Native Windows window creation and management
- Event-driven architecture
- Simple and clean API
- Lightweight and minimal dependencies
- Easy integration with existing projects
- Cross-platform support (Windows, with Linux/macOS coming soon)

## Installation

### Windows

#### Method 1: Pre-built Binary
1. Download the latest release from the releases page
2. Extract the archive to a location of your choice
3. Add the `bin` directory to your system's PATH
4. Copy `include/easyui.h` to your compiler's include directory
5. Copy `lib/libeasyui.a` to your compiler's lib directory

#### Method 2: Build from Source
```bash
git clone https://github.com/yourusername/easyui.git
cd easyui
mingw32-make
mingw32-make install
```

### Using with CMake
Add these lines to your CMakeLists.txt:
```cmake
find_package(EasyUI REQUIRED)
target_link_libraries(your_project PRIVATE EasyUI::easyui)
```

### Using with pkg-config
```bash
gcc your_program.c `pkg-config --cflags --libs easyui` -o your_program
```

## Basic Usage

### 1. Include the Header
```c
#include <easyui.h>
```

### 2. Create a Window
```c
int main() {
    // Create a window
    EUI_Window* window = EUI_CreateWindow("My App", 100, 100, 800, 600);
    if (!window) {
        return 1;
    }

    // Show the window
    EUI_ShowWindow(window);

    // Start the message loop
    EUI_ProcessMessages();

    return 0;
}
```

### 3. Handle Events
```c
void onPaint(EUI_Window* window) {
    // Draw your content here
}

void onClick(EUI_Window* window, EUI_Point point) {
    printf("Clicked at (%d, %d)\n", point.x, point.y);
}

int main() {
    EUI_Window* window = EUI_CreateWindow("My App", 100, 100, 800, 600);
    
    // Set event handlers
    window->onPaint = onPaint;
    window->onClick = onClick;
    
    EUI_ShowWindow(window);
    EUI_ProcessMessages();
    return 0;
}
```

## Building Your Project

### With MinGW (Windows)
```bash
gcc -I/usr/local/include your_program.c -L/usr/local/lib -leasyui -lgdi32 -luser32 -o your_program
```

### With Visual Studio
1. Add the include directory to your project settings
2. Add the library directory to your project settings
3. Add `easyui.lib`, `gdi32.lib`, and `user32.lib` to your linker input

### With CMake
```cmake
cmake_minimum_required(VERSION 3.10)
project(YourProject C)

find_package(EasyUI REQUIRED)

add_executable(your_program your_program.c)
target_link_libraries(your_program PRIVATE EasyUI::easyui)
```

## Documentation

### Window Management
```c
// Create a window
EUI_Window* EUI_CreateWindow(const char* title, int x, int y, int width, int height);

// Show a window
void EUI_ShowWindow(EUI_Window* window);

// Destroy a window
void EUI_DestroyWindow(EUI_Window* window);

// Process window messages
void EUI_ProcessMessages(void);
```

### Event Handlers
```c
// Window paint event
void (*onPaint)(EUI_Window* window);

// Mouse click event
void (*onClick)(EUI_Window* window, EUI_Point point);
```

## Examples

Check the `examples` directory for more examples:
- Basic window creation
- Event handling
- Custom drawing
- Controls usage

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Support

- GitHub Issues: [Report a bug](https://github.com/yourusername/easyui/issues)
- Documentation: [Full API Reference](https://yourusername.github.io/easyui/docs)
- Examples: [Example Gallery](https://yourusername.github.io/easyui/examples)
