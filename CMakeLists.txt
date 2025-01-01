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

# Platform-specific source files
set(PLATFORM_SOURCES "")
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

# Core library sources
set(CORE_SOURCES
    src/easyui.c
)

# Create the library
add_library(easyui ${CORE_SOURCES} ${PLATFORM_SOURCES})
add_library(EasyUI::easyui ALIAS easyui)

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
    target_link_libraries(easyui PRIVATE ${X11_LIBRARIES})
    target_include_directories(easyui PRIVATE ${X11_INCLUDE_DIR})
elseif(EASYUI_PLATFORM_MACOS)
    target_link_libraries(easyui PRIVATE ${COCOA_LIBRARY})
    set_source_files_properties(
        src/platform/macos/window.m
        src/platform/macos/graphics.m
        PROPERTIES
        COMPILE_FLAGS "-x objective-c"
    )
endif()

# Installation
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS easyui
    EXPORT EasyUITargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    FILES
        include/easyui.h
        "${CMAKE_CURRENT_BINARY_DIR}/include/easyui_platform.h"
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/easyui
)

# Export targets
install(EXPORT EasyUITargets
    FILE EasyUITargets.cmake
    NAMESPACE EasyUI::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/EasyUI
)

# Create config file
configure_package_config_file(
    cmake/EasyUIConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/EasyUIConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/EasyUI
)

# Create version file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/EasyUIConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Install config files
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/EasyUIConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/EasyUIConfigVersion.cmake"
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/EasyUI
)

# Examples
if(WIN32)
    add_subdirectory(examples)
else()
    message(STATUS "Examples are currently only supported on Windows")
endif()

# Testing
enable_testing()
add_subdirectory(tests)
