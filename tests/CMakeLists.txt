include(FetchContent)

add_executable(tests
    tests_scalar.cpp
    tests_vector.cpp
    tests_quat.cpp
)

include(GoogleTest)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8   # or newer stable
)
FetchContent_MakeAvailable(glm)

target_link_libraries(tests 
    PRIVATE 
        nem
        gtest_main
        glm::glm
)
set_target_properties(tests PROPERTIES FOLDER "Tests")

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -C $<CONFIG>
    DEPENDS tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Building and running all tests..."
)
gtest_discover_tests(tests)