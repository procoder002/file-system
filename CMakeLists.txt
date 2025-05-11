cmake_minimum_required(VERSION 2.8)

project(file_system)

# Compiler and flags
set(CMAKE_CXX_STANDARD 11)  # Or a more recent standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g") # Add -Wall and -Wextra

# Include directory
include_directories(./include)

# Source files
set(SRCS
    src/client.cpp
    src/shell.cpp
    src/file_system.cpp
    src/tree_node.cpp
    src/utility.cpp
)

# Output binary (if you want to create an executable as well)
set(BINARY shell)


# Create the executable
add_executable(${BINARY} ${SRCS})
