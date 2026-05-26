include(../cmake/CompilerWarnings.cmake)
include(../cmake/ClangTidy.cmake)

add_library(nem INTERFACE)
target_include_directories(nem INTERFACE include)
set_target_properties(nem PROPERTIES FOLDER "Library")

# compiler warnings
option(ENABLE_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
option(ENABLE_STRICT_WARNINGS "Enable extra strict warnings" ON)

# nem
option(ANEM_ERR_THROW  "Throw C++ exceptions on errors" OFF)
option(ANEM_ERR_LOG    "Print errors to console" ON)
option(ANEM_ERR_SAFE_FALLBACK   "Safely fallback to a valid, but possibly logically incorrect value" OFF)
option(ANEM_ERR_USE_NAN   "Fallback to NANs explicitly" ON)
option(ANEM_HIGH_PRECISION  "Use double instead of float" OFF)
option(ANEM_NO_INLINE "Disable inlining" OFF)

if(ANEM_ERR_THROW)
    target_compile_definitions(nem INTERFACE NEM_ERR_THROW)
else()
    if(ANEM_ERR_SAFE_FALLBACK)
        target_compile_definitions(nem INTERFACE NEM_ERR_SAFE_FALLBACK)
    endif()
    if(ANEM_ERR_USE_NAN)
        target_compile_definitions(nem INTERFACE NEM_ERR_USE_NAN)
    endif()
endif()

if(ANEM_ERR_LOG)
    target_compile_definitions(nem INTERFACE NEM_ERR_LOG)
endif()

if(ANEM_HIGH_PRECISION)
    target_compile_definitions(nem INTERFACE NEM_USE_DOUBLE_PRECISION)
endif()

if(ANEM_NO_INLINE)
    target_compile_definitions(nem INTERFACE NEM_NO_INLINE)
endif()

# warnings
set_project_warnings(nem)
