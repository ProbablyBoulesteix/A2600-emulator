cmake_minimum_required(VERSION 3.18)
project(A2600_emulator LANGUAGES CXX)

# Settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # For IDE support
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# External dependencies

# Source files
add_executable(A2600_emulator src/CPU/main.cpp)

# Internal dependencies/imports
target_include_directories(A2600_emulator PRIVATE include, defs)



