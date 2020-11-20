# minimum of CMake 3.12 needed for nana
cmake_minimum_required(VERSION 3.12-3.18 FATAL_ERROR)

add_executable(print
    print.cpp
)

include(FetchContent)

if(MSVC)
  FetchContent_Declare(
    nana
    GIT_REPOSITORY https://github.com/cnjinhao/nana.git
    GIT_TAG        develop-1.8
  )
else()
  FetchContent_Declare(
    nana
    GIT_REPOSITORY https://github.com/cnjinhao/nana.git
    GIT_TAG        master
  )
endif()

FetchContent_GetProperties(nana)
if(NOT nana_POPULATED)
  FetchContent_Populate(nana)
  add_subdirectory(${nana_SOURCE_DIR} ${nana_BINARY_DIR})
endif()

include_directories(
    ../../include
)

target_link_libraries(print
    cupsprint
    nana
)

target_compile_features(print
    PUBLIC
    cxx_std_17
)