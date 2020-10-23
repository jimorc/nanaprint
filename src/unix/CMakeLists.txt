# minimum of CMake 3.12 needed for nana
cmake_minimum_required(VERSION 3.12-3.18 FATAL_ERROR)

include(FindCups)

add_library(cupsprint
    printers.cpp
    printer.cpp
    mediasizes.cpp
    mediasize.cpp
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

