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
    colormode.cpp
    side.cpp
    pagesetup.cpp
    printsettings.cpp
    printoperation.cpp
    printdialog.cpp
    printdialogsettings.cpp
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
    nana
)

target_compile_features(cupsprint
    PUBLIC
    cxx_std_17
)