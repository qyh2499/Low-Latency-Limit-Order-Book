# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(AVLTestProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(./AVL)

set(SOURCES
    ./tests/AVLtest.cpp
)

# Create the executable
add_executable(AVLTest ${SOURCES})
