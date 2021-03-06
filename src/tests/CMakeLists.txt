# version 3.11 or later of CMake or needed later for installing GoogleTest
cmake_minimum_required(VERSION 3.11-3.18)

include(GoogleTest)
include(CTest)
include(FetchContent)

enable_testing()

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

macro(package_add_test_with_libraries TESTNAME FILES LIBRARIES TEST_WORKING_DIRECTORY)
    add_executable(${TESTNAME} ${FILES})
    target_link_libraries(${TESTNAME} gtest gmock gtest_main ${LIBRARIES})
    gtest_discover_tests(${TESTNAME}
        WORKING_DIRECTORY ${TEST_WORKING_DIRECTORY}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${TEST_WORKING_DIRECTORY}"
    )
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

include_directories(
#    ${CUPS_INCLUDE_DIRS}
    ../../include
)

package_add_test_with_libraries(IterTests
    itertests.cpp 
    nana_print 
    "${PROJECT_DIR}"
)

package_add_test_with_libraries(MediaSizesTranslatorUnixTests
    mediasizestranslatorunixtests.cpp 
    nana_print 
    "${PROJECT_DIR}"
)

package_add_test_with_libraries(MediaSizeTests
    mediasizetests.cpp 
    nana_print 
    "${PROJECT_DIR}"
)

package_add_test_with_libraries(PageOrientationTests
    pageorientationtests.cpp 
    nana_print 
    "${PROJECT_DIR}"
)

package_add_test_with_libraries(PrintQualityTests
    printqualitytests.cpp 
    nana_print 
    "${PROJECT_DIR}"
)

package_add_test_with_libraries(PrintFinishingsTests
    finishingstests.cpp 
    nana_print 
    "${PROJECT_DIR}"
)

package_add_test_with_libraries(MediaSourceTests
    mediasourcetests.cpp 
    nana_print 
    "${PROJECT_DIR}"
)

package_add_test_with_libraries(MediaTypeTests
    mediatypetests.cpp 
    nana_print 
    "${PROJECT_DIR}"
)

package_add_test_with_libraries(ColorModeTests
    colormodetests.cpp 
    nana_print 
    "${PROJECT_DIR}"
)

package_add_test_with_libraries(SideTests
    sidetests.cpp 
    nana_print 
    "${PROJECT_DIR}"
)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(
#        /Wall 
#         /WX
    )
else()
    # lots of warnings and all warnings as errors
    target_compile_options(IterTests
        PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
    )
    target_compile_features(IterTests
        PUBLIC
        cxx_std_17
    )
    
    target_compile_options(MediaSizesTranslatorUnixTests
        PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
    )
    target_compile_features(MediaSizesTranslatorUnixTests
        PUBLIC
        cxx_std_17
    )
    
    target_compile_options(MediaSizeTests
        PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
    )
    target_compile_features(MediaSizeTests
        PUBLIC
        cxx_std_17
    )
    
    target_compile_options(PageOrientationTests
        PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
    )
    target_compile_features(PageOrientationTests
        PUBLIC
        cxx_std_17
    )
    
    target_compile_options(PrintQualityTests
        PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
    )
    target_compile_features(PrintQualityTests
        PUBLIC
        cxx_std_17
    )
    
    target_compile_options(PrintFinishingsTests
        PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
    )
    target_compile_features(PrintFinishingsTests
        PUBLIC
        cxx_std_17
    )
    
    target_compile_options(MediaSourceTests
        PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
    )
    target_compile_features(MediaSourceTests
        PUBLIC
        cxx_std_17
    )
    
    target_compile_options(MediaTypeTests
        PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
    )
    target_compile_features(MediaTypeTests
        PUBLIC
        cxx_std_17
    )
    
        target_compile_options(ColorModeTests
        PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
    )
    target_compile_features(ColorModeTests
        PUBLIC
        cxx_std_17
    )
    
    target_compile_options(SideTests
        PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
    )
    target_compile_features(SideTests
        PUBLIC
        cxx_std_17
    )
    
endif()
