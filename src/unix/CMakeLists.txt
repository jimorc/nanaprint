# minimum of CMake 3.12 needed for nana
cmake_minimum_required(VERSION 3.12-3.18 FATAL_ERROR)

add_library(cupsprint
    printers.cpp
)

include_directories(
    ../../include
)
