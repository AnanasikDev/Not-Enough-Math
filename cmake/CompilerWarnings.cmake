function(set_project_warnings target)

    set(MSVC_WARNINGS
        /W4
        /permissive-
        /diagnostics:caret
    )

    set(CLANG_WARNINGS
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wshadow
        -fdiagnostics-color=always
    )

    if(ENABLE_WARNINGS_AS_ERRORS)
        list(APPEND MSVC_WARNINGS /WX)
        list(APPEND CLANG_WARNINGS -Werror)
    endif()

    if(MSVC)
        target_compile_options(${target} INTERFACE ${MSVC_WARNINGS})
    else()
        target_compile_options(${target} INTERFACE ${CLANG_WARNINGS})
    endif()

endfunction()