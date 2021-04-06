# minimum of CMake 3.12 needed for nana
cmake_minimum_required(VERSION 3.12-3.18 FATAL_ERROR)

add_executable(printerproperties
    printerproperties.cpp
)

include_directories(
    ../../include
)

target_link_libraries(printerproperties
    nana_print
)

if (MSVC)
    # warning level 4 and all warnings as errors
    target_compile_options(printerproperties
        PRIVATE
        /Wall 
        /WX
    )
else()
    # lots of warnings and all warnings as errors
    target_compile_options(printerproperties
        PRIVATE
        -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
endif()


target_compile_features(printerproperties
    PUBLIC
    cxx_std_17
)