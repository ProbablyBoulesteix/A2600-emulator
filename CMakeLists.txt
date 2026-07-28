cmake_minimum_required(VERSION 3.28)
project(A2600_emulator LANGUAGES CXX)

# Settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # For IDE support
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# External dependencies

# Internal dependencies/imports
target_include_directories(A2600_emulator PRIVATE include)

