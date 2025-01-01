cmake_minimum_required(VERSION 3.10)
project(EasyUI VERSION 0.1.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Platform detection and configuration
if(WIN32)
    set(EASYUI_PLATFORM "WINDOWS")
    set(PLATFORM_SOURCES
        src/platform/windows/window.c
        src/platform/windows/graphics.c
    )
    set(PLATFORM_LIBS gdi32 user32)
elseif(UNIX AND NOT APPLE)
    set(EASYUI_PLATFORM "LINUX")
    set(PLATFORM_SOURCES
        src/platform/linux/window.c
        src/platform/linux/graphics.c
    )
    set(PLATFORM_LIBS X11)
    # Find X11
    find_package(X11 REQUIRED)
    if(NOT X11_FOUND)
        message(FATAL_ERROR "X11 development files not found")
    endif()
    include_directories(${X11_INCLUDE_DIR})
elseif(APPLE)
    set(EASYUI_PLATFORM "MACOS")
    set(PLATFORM_SOURCES
        src/platform/macos/window.c
        src/platform/macos/graphics.c
    )
    set(PLATFORM_LIBS "-framework Cocoa")
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Configure platform-specific header
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/easyui_platform.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/easyui_platform.h
)

# Library source files
set(EASYUI_SOURCES
    src/easyui.c
    src/styles/styles.c
    src/window/window.c
    src/graphics/graphics.c
    ${PLATFORM_SOURCES}
)

# Create the library
add_library(easyui STATIC ${EASYUI_SOURCES})

# Include directories
target_include_directories(easyui
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Platform-specific libraries
target_link_libraries(easyui PRIVATE ${PLATFORM_LIBS})

# Platform-specific definitions
target_compile_definitions(easyui 
    PUBLIC
        EASYUI_PLATFORM_${EASYUI_PLATFORM}
)

# Examples
if(WIN32)
    add_subdirectory(examples)
else()
    message(STATUS "Examples are currently only supported on Windows")
endif()

# Installation
install(TARGETS easyui
    EXPORT easyui-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(FILES 
    include/easyui.h
    ${CMAKE_CURRENT_BINARY_DIR}/include/easyui_platform.h
    DESTINATION include
)

install(EXPORT easyui-targets
    FILE EasyUITargets.cmake
    NAMESPACE EasyUI::
    DESTINATION lib/cmake/easyui
)

# Create and install config file
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/EasyUIConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/EasyUIConfig.cmake
    INSTALL_DESTINATION lib/cmake/easyui
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/EasyUIConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/EasyUIConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/EasyUIConfigVersion.cmake
    DESTINATION lib/cmake/easyui
)

# Testing
if(WIN32)
    enable_testing()
    add_subdirectory(tests)
endif()
