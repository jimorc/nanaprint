# minimum of CMake 3.12 needed for nana
cmake_minimum_required(VERSION 3.12-3.18 FATAL_ERROR)

add_executable(printerproperties
    printerproperties.cpp
)

target_compile_features(printerproperties
    PUBLIC
    cxx_std_20
)