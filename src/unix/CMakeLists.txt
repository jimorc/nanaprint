# minimum of CMake 3.12 needed for nana
cmake_minimum_required(VERSION 3.12-3.18 FATAL_ERROR)

include(FindCups)

add_library(cupsprint
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
)

link_directories(
    ${CUPS_LIBRARY_DIRS}
)


include_directories(
    ${CUPS_INCLUDE_DIRS}
    ../../include
)

target_link_libraries(cupsprint
    ${CUPS_LIBRARIES}
)

target_compile_features(printerproperties
    PUBLIC
    cxx_std_17
)