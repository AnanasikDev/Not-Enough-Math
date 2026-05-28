cmake_minimum_required(VERSION 3.31)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(NotEnoughMath LANGUAGES CXX)

set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/_deps" CACHE PATH "")

if ($CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(_DEBUG)
elseif ($CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(_RELEASE)
endif()

include(CTest)

# This makes the sub-projects appear as folders in VS
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (MSVC)
    add_compile_options(/Zc:__cplusplus)
endif()

option(NEM_BUILD_TESTS "Build tests" ON)
option(NEM_BUILD_BENCH "Build benchmarks" ON)
option(NEM_BUILD_DEMO  "Build demo" ON)

add_library(nem INTERFACE)
target_include_directories(nem INTERFACE nem/include/)

if(NEM_BUILD_TESTS)
    add_subdirectory(tests)
endif()
if(NEM_BUILD_BENCH)
    add_subdirectory(bench)
endif()
if(NEM_BUILD_DEMO)
    add_subdirectory(demo)
endif()