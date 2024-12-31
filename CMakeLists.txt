cmake_minimum_required(VERSION 3.10)
project(EasyUI VERSION 0.1.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Library source files
set(EASYUI_SOURCES
    src/easyui.c
)

# Create the library
add_library(easyui STATIC ${EASYUI_SOURCES})

# Include directories
target_include_directories(easyui
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Windows-specific libraries
if(WIN32)
    target_link_libraries(easyui PRIVATE gdi32 user32)
endif()

# Examples
add_subdirectory(examples)

# Installation
install(TARGETS easyui
    EXPORT easyui-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(FILES include/easyui.h DESTINATION include)

# Testing
enable_testing()
add_subdirectory(tests)
