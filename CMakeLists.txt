cmake_minimum_required(VERSION 3.31)
project(NotEnoughMath LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/_deps" CACHE PATH "")

include(CTest)

# This makes the sub-projects appear as folders in VS
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (MSVC)
    add_compile_options(/Zc:__cplusplus)
endif()

add_subdirectory(nem)
add_subdirectory(tests)
add_subdirectory(demo)
add_subdirectory(bench)