#!/bin/bash

# Default installation prefix
PREFIX="/usr/local"

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --prefix=*)
            PREFIX="${1#*=}"
            shift
            ;;
        --help)
            echo "Usage: $0 [options]"
            echo "Options:"
            echo "  --prefix=PATH    Installation prefix (default: /usr/local)"
            echo "  --help           Show this help message"
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            echo "Use --help for usage information"
            exit 1
            ;;
    esac
done

# Function to handle errors
handle_error() {
    echo "Error: $1"
    exit 1
}

# Create build directory
echo "Creating build directory..."
mkdir -p build || handle_error "Failed to create build directory"
cd build || handle_error "Failed to enter build directory"

# Configure with CMake
echo "Configuring with CMake..."
cmake .. \
    -DCMAKE_INSTALL_PREFIX="$PREFIX" \
    -DCMAKE_BUILD_TYPE=Release || handle_error "CMake configuration failed"

# Build
echo "Building..."
cmake --build . || handle_error "Build failed"

# Run tests
echo "Running tests..."
ctest --output-on-failure || handle_error "Tests failed"

# Install
echo "Installing... (may require sudo)"
sudo cmake --install . || handle_error "Installation failed"

# Update library cache
echo "Updating library cache..."
sudo ldconfig || handle_error "Failed to update library cache"

echo "Installation completed successfully!"
echo "Installation prefix: $PREFIX"
echo ""
echo "To use EasyUI in your projects:"
echo "1. Include the header: #include <easyui/easyui.h>"
echo "2. Link with the library: -leasyui"
echo ""
echo "Example compile command:"
echo "gcc -o myapp myapp.c -leasyui"
