cmake_minimum_required(VERSION 3.31)
project(NotEnoughMath LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This makes the sub-projects appear as folders in VS
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(CTest) # Enables the 'ctest' command and VS Test Explorer integration
include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(nem)
add_subdirectory(tests)
add_subdirectory(demo)