cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(gtest-demo)

enable_language(C)
enable_language(CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS         "-Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    )

add_library(
    maths
    src/maths.cpp
    )

set(GOOGLETEST_ROOT external/googletest/googletest CACHE STRING "Google Test source root")
set(GOOGLEMOCK_ROOT external/googletest/googlemock CACHE STRING "Google Mock source root")

include_directories(
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
    ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}
    ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}/include
    )

set(GOOGLETEST_SOURCES
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
    )

set(GOOGLEMOCK_SOURCES
    ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}/src/gmock-all.cc
    ${PROJECT_SOURCE_DIR}/${GOOGLEMOCK_ROOT}/src/gmock_main.cc
    )

foreach(_source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

foreach(_source ${GOOGLEMOCK_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(googletest ${GOOGLETEST_SOURCES})
add_library(googlemock ${GOOGLEMOCK_SOURCES})

add_executable(
    unit_tests
    src/main.cpp
    src/maths.cpp
    test/test.cpp
    )

add_dependencies(unit_tests googletest)

target_link_libraries(
    unit_tests
    googletest
    googlemock
    maths
    pthread
    )

include(CTest)
enable_testing()

add_test(unit ${PROJECT_BINARY_DIR}/unit_tests)