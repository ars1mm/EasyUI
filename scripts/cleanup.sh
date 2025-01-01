#!/bin/bash
echo "Cleaning up build files..."

# Remove build directory and object files
rm -rf build/
rm -f *.o

# Remove CMake generated files
rm -rf CMakeFiles/
rm -f CMakeCache.txt
rm -f cmake_install.cmake

# Remove generated files
rm -f include/easyui_platform.h
rm -f easyui.pc

# Clean test build files
rm -rf tests/CMakeFiles/
rm -f tests/*.o

echo "Cleanup complete!"
