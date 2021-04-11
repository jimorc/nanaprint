# minimum of CMake 3.12 needed for nana
cmake_minimum_required(VERSION 3.12-3.18 FATAL_ERROR)

include(FindCups)

include(FetchContent)

FetchContent_Declare(
    nana
    GIT_REPOSITORY https://github.com/cnjinhao/nana.git
    GIT_TAG        develop-1.8
)

FetchContent_GetProperties(nana)
if(NOT nana_POPULATED)
  FetchContent_Populate(nana)
  add_subdirectory(${nana_SOURCE_DIR} ${nana_BINARY_DIR})
endif()

if (WIN32)
    set(PRINT_LIBRARIES "")
    set(OS_DIR win32)
else ()
    set(PRINT_LIBRARIES ${CUPS_LIBRARIES})
    set(OS_DIR unix)
endif ()

add_library(nana_print
    ${OS_DIR}/printers.cpp
    ${OS_DIR}/printer.cpp
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
    if (NOT WIN32)
        ${CUPS_LIBRARY_DIRS}
    endif ()
)


include_directories(
    if (NOT WIN32)
        ${CUPS_INCLUDE_DIRS}
    endif ()
    ../include
)

if (MSVC)
    # warning level 4 and all warnings as errors
    target_compile_options(nana_print
        PRIVATE
        /Wv:18
#        /Wall
#        /WX
    )
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
    ${PRINT_LIBRARIES}
    nana
)

target_compile_features(nana_print
    PUBLIC
    cxx_std_17
)

if(PROJECT_NAME STREQUAL nanaprint AND NOT WIN32)
    add_subdirectory(tests)
endif() #PROJECT_NAME STREQUAL nanaprint