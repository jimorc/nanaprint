# minimum of CMake 3.12 needed for nana
cmake_minimum_required(VERSION 3.12-3.18 FATAL_ERROR)

add_executable(printerproperties
    printerproperties.cpp
)

include_directories(
    ../../include
)

target_link_libraries(printerproperties
    cupsprint
)

target_compile_features(printerproperties
    PUBLIC
    cxx_std_20
)