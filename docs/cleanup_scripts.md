# Cleanup Scripts

EasyUI provides cleanup scripts for both Windows and Unix-like systems to help you clean build artifacts and temporary files from your project directory.

## Available Scripts

### Windows (cleanup.bat)

Location: `scripts/cleanup.bat`

This batch script removes build artifacts on Windows systems. To use it:

```batch
cd path/to/EasyUI
scripts\cleanup.bat
```

### Unix (cleanup.sh)

Location: `scripts/cleanup.sh`

This shell script removes build artifacts on Unix-like systems (Linux, macOS). To use it:

```bash
cd path/to/EasyUI
chmod +x scripts/cleanup.sh  # Make the script executable (first time only)
./scripts/cleanup.sh
```

## What Gets Cleaned

The cleanup scripts will remove the following:

- Build directory (`build/`)
- Object files (`*.o`)
- CMake generated files:
  - `CMakeFiles/` directory
  - `CMakeCache.txt`
  - `cmake_install.cmake`
- Generated platform header (`include/easyui_platform.h`)
- Test build files:
  - Test object files
  - Test CMake files
- Generated pkg-config file (`easyui.pc`)

## When to Use

Run these scripts when you want to:
- Clean up your workspace
- Perform a fresh build
- Switch between different build configurations
- Troubleshoot build issues
- Before committing to version control (if build artifacts aren't ignored)

## Note

Make sure to save any important work before running the cleanup scripts, as they will permanently delete the specified files and directories.
