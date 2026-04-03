include(FetchContent)

add_executable(tests 
    tests_main.cpp
)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)
include(Catch) # makes tests show up in Visual Studio's Test Explorer
catch_discover_tests(tests)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8   # or newer stable
)
FetchContent_MakeAvailable(glm)

target_link_libraries(tests 
    PRIVATE 
        nem
        Catch2::Catch2WithMain
        glm::glm
)

set_target_properties(tests PROPERTIES FOLDER "Tests")
