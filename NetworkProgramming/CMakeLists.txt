cmake_minimum_required(VERSION 3.10)
project(NetworkProgramming VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Library source files
set(LIB_SOURCES
    src/socket.cpp
    src/serverTCP.cpp
    src/clientTCP.cpp
    src/serverTCPdaytime.cpp
    src/clientTCPdaytime.cpp
)

# Create static library
add_library(networklib STATIC ${LIB_SOURCES})

# Server executable
add_executable(test_serverTCP examples/test_serverTCP.cpp)
target_link_libraries(test_serverTCP networklib)

# Client executable
add_executable(test_clientTCP examples/test_clientTCP.cpp)
target_link_libraries(test_clientTCP networklib)

# Daytime Server executable
add_executable(test_serverTCPdaytime examples/test_serverTCPdaytime.cpp)
target_link_libraries(test_serverTCPdaytime networklib)

# Daytime Client executable
add_executable(test_clientTCPdaytime examples/test_clientTCPdaytime.cpp)
target_link_libraries(test_clientTCPdaytime networklib)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
