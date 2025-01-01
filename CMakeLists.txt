cmake_minimum_required(VERSION 3.10)
project(EasyUI VERSION 1.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Platform detection
if(WIN32)
    set(EASYUI_PLATFORM_WINDOWS TRUE)
elseif(UNIX AND NOT APPLE)
    set(EASYUI_PLATFORM_LINUX TRUE)
elseif(APPLE)
    set(EASYUI_PLATFORM_MACOS TRUE)
    enable_language(OBJC)
    set(CMAKE_OBJC_FLAGS "${CMAKE_OBJC_FLAGS} -fobjc-arc")
endif()

# Configure platform-specific header
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/easyui_platform.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/easyui_platform.h"
)

# Core library sources
set(CORE_SOURCES
    src/easyui.c
)

# Platform-specific source files
if(EASYUI_PLATFORM_WINDOWS)
    set(PLATFORM_SOURCES
        src/platform/windows/window.c
        src/platform/windows/graphics.c
    )
elseif(EASYUI_PLATFORM_LINUX)
    set(PLATFORM_SOURCES
        src/platform/linux/window.c
        src/platform/linux/graphics.c
    )
    find_package(X11 REQUIRED)
elseif(EASYUI_PLATFORM_MACOS)
    set(PLATFORM_SOURCES
        src/platform/macos/window.m
        src/platform/macos/graphics.m
    )
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
endif()

# Create the library
add_library(easyui ${CORE_SOURCES} ${PLATFORM_SOURCES})

# Include directories
target_include_directories(easyui
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Platform-specific dependencies
if(EASYUI_PLATFORM_WINDOWS)
    target_link_libraries(easyui PRIVATE gdi32 user32)
elseif(EASYUI_PLATFORM_LINUX)
    target_link_libraries(easyui PRIVATE X11)
    target_include_directories(easyui PRIVATE ${X11_INCLUDE_DIR})
elseif(EASYUI_PLATFORM_MACOS)
    target_link_libraries(easyui PRIVATE ${COCOA_LIBRARY})
endif()

# Testing
enable_testing()

# Add test executable
add_executable(easyui_tests tests/main.c)
target_link_libraries(easyui_tests PRIVATE easyui)

# Add test
add_test(NAME easyui_test COMMAND easyui_tests)
