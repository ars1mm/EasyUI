# Installing EasyUI on Linux

## Quick Installation

For a quick installation with default settings:

```bash
# Clone the repository
git clone https://github.com/ars1mm/EasyUI.git
cd EasyUI

# Make scripts executable
chmod +x scripts/*.sh

# Install dependencies
./scripts/install_dependencies.sh

# Build and install
./scripts/build_and_install.sh
```

## Custom Installation

You can customize the installation prefix:

```bash
./scripts/build_and_install.sh --prefix=/usr
```

## Manual Installation

If you prefer to install manually:

1. Install dependencies:
   - For Ubuntu/Debian:
     ```bash
     sudo apt-get update
     sudo apt-get install build-essential cmake libx11-dev pkg-config
     ```
   - For Fedora:
     ```bash
     sudo dnf install gcc gcc-c++ cmake libX11-devel make pkg-config
     ```
   - For Arch Linux:
     ```bash
     sudo pacman -Sy base-devel cmake libx11 pkg-config
     ```

2. Build and install:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   sudo make install
   sudo ldconfig
   ```

## Usage

After installation, you can use EasyUI in your projects:

```c
#include <easyui/easyui.h>

int main() {
    struct EUI_Window* window = EUI_CreateWindow("My Window", 100, 100, 800, 600);
    EUI_ShowWindow(window);
    // ... your code here ...
    EUI_DestroyWindow(window);
    return 0;
}
```

Compile your program:
```bash
gcc -o myapp myapp.c -leasyui
```

## Troubleshooting

1. If you get a library not found error:
   ```bash
   sudo ldconfig
   ```

2. If headers are not found, verify the installation prefix:
   ```bash
   pkg-config --cflags easyui
   ```

3. For other issues, please check:
   - The installation log
   - System requirements
   - Compiler version (GCC 4.8 or later recommended)

## Uninstallation

To uninstall EasyUI:
```bash
cd build
sudo make uninstall
```
