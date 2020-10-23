# minimum of CMake 3.12 needed for nana
cmake_minimum_required(VERSION 3.12-3.18 FATAL_ERROR)

project(nanaprint
    VERSION 0.1
    LANGUAGES CXX
)

add_subdirectory(apps)