find_program(CLANG_TIDY_EXE NAMES clang-tidy)

if(CLANG_TIDY_EXE)
    add_custom_target(run_clang_tidy
        COMMAND ${CLANG_TIDY_EXE}
            -p=${CMAKE_BINARY_DIR}
            --use-color
            --extra-arg=-fdiagnostics-color=always
            ${CMAKE_SOURCE_DIR}/src/dummy.cpp
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running clang-tidy on all project sources..."
        VERBATIM
    )
endif()