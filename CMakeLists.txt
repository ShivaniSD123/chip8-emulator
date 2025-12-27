cmake_minimum_required(VERSION 3.15)
project(chip8-emulator CXX)

include(cmake/StandardProjectSettings.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/CPM.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)
add_library(project_warnings INTERFACE)

add_subdirectory(src)