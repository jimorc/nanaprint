# minimum of CMake 3.12 needed for nana
cmake_minimum_required(VERSION 3.12-3.18 FATAL_ERROR)

project(nanaprint
    VERSION 0.1
    LANGUAGES CXX
)
if (MSVC)
    add_compile_options(
        /MT$<$<CONFIG:Debug>:d>
        /Wv:18
    )
endif ()
add_subdirectory(apps)
add_subdirectory(src)