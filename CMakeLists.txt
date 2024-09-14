# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and type
project(OrderBookProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/order_book)
include_directories(${PROJECT_SOURCE_DIR}/AVL)


set(HEADERS
    ./order_book/Book.hpp
    ./order_book/Limit.hpp
    ./order_book/Order.hpp
    ./AVL/AVLTree.hpp
    ./AVL/AVLTreeNode.hpp
    ./order_generator/orderGenerator.hpp
    ./order_generator/orderProcessTimer.hpp
)

set(SOURCES
    ./order_book/Book.cpp
    ./order_book/Limit.cpp
    ./order_book/Order.cpp
    ./order_generator/orderGenerator.cpp
    ./order_generator/orderProcessTimer.cpp
)

# Define the library target
add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})

# Define the executable target and include SOURCES to ensure linking
add_executable(${PROJECT_NAME} ./main.cpp)

# Link the executable with the library
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
