# minimum of CMake 3.12 needed for nana
cmake_minimum_required(VERSION 3.12-3.18 FATAL_ERROR)

include(FindCups)

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
    GIT_TAG        develop-1.8
  )
endif()

FetchContent_GetProperties(nana)
if(NOT nana_POPULATED)
  FetchContent_Populate(nana)
  add_subdirectory(${nana_SOURCE_DIR} ${nana_BINARY_DIR})
endif()

add_library(nana_print
    printers.cpp
    printer.cpp
    mediasizes.cpp
    mediasize.cpp
    mediasizestranslator.cpp
    pageorientation.cpp
    printquality.cpp
    finishings.cpp
    mediasource.cpp
    mediatype.cpp
    colormode.cpp
    side.cpp
    pagesetup.cpp
    printsettings.cpp
    printoperation.cpp
    printdialog.cpp
    printdialogsettings.cpp
    basicpanel.cpp
)

link_directories(
    ${CUPS_LIBRARY_DIRS}
)


include_directories(
    ${CUPS_INCLUDE_DIRS}
    ../../include
)

if (MSVC)
    # warning level 4 and all warnings as errors
    target_compile_options(nana_print
        PRIVATE
        /Wall
        /WX)
else()
    # lots of warnings and all warnings as errors
    target_compile_options(nana_print
        PRIVATE
        -Wall 
        -Wextra 
        -pedantic 
        -Werror)
endif()

target_link_libraries(nana_print
    ${CUPS_LIBRARIES}
    nana
)

target_compile_features(nana_print
    PUBLIC
    cxx_std_17
)