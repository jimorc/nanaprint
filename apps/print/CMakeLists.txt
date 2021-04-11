# minimum of CMake 3.12 needed for nana
cmake_minimum_required(VERSION 3.12-3.18 FATAL_ERROR)

add_executable(print
    print.cpp
)

include_directories(
    ../../include
)

if (MSVC)
    # warning level 4 and all warnings as errors
    target_compile_options(print
        PRIVATE
        /MT$<$<CONFIG:Debug>:d>
#        /Wall 
#        /WX
    )
else()
    # lots of warnings and all warnings as errors
    target_compile_options(print
        PRIVATE
        -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
endif()

target_link_libraries(print
    nana_print
    nana
)

target_compile_features(print
    PUBLIC
    cxx_std_17
)