find_package(Python3 REQUIRED COMPONENTS Interpreter)
find_program(RUN_CLANG_TIDY_PY
    NAMES run-clang-tidy.py run-clang-tidy
)

if(Python3_FOUND AND RUN_CLANG_TIDY_PY)

    file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/*.hpp
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/tests/*.cpp
        ${CMAKE_SOURCE_DIR}/tests/*.hpp
        ${CMAKE_SOURCE_DIR}/tests/*.h
    )

    add_custom_target(run_clang_tidy
        COMMAND ${CLANG_TIDY_EXE}
            -p=${CMAKE_BINARY_DIR}
            ${ALL_CXX_SOURCE_FILES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running clang-tidy on all project sources..."
        VERBATIM
    )

endif()