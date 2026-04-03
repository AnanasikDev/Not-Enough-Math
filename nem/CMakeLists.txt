add_library(nem STATIC 
    src/nem.cpp
    include/config.hpp
    include/nan.hpp
    include/err.hpp
    include/nem.hpp
    include/utils.hpp
    include/vec.hpp
    include/vec_io.hpp
    include/vec_utils.hpp
    include/sys.hpp
)

target_include_directories(nem PUBLIC include)
set_target_properties(nem PROPERTIES FOLDER "Library")

option(ANEM_ERR_THROW  "Throw C++ exceptions on errors" OFF)
option(ANEM_ERR_LOG    "Print errors to console" ON)
option(ANEM_ERR_SAFE_FALLBACK   "Safely fallback to a valid, but possibly logically incorrect value" OFF)
option(ANEM_ERR_USE_NAN   "Fallback to NANs explicitly" ON)

option(ANEM_HIGH_PRECISION  "Use double instead of float" OFF)

if(ANEM_ERR_THROW)
    target_compile_definitions(nem PUBLIC NEM_ERR_THROW)
else()
    if(ANEM_ERR_SAFE_FALLBACK)
        target_compile_definitions(nem PUBLIC NEM_ERR_SAFE_FALLBACK)
    endif()
    if(ANEM_ERR_USE_NAN)
        target_compile_definitions(nem PUBLIC NEM_ERR_USE_NAN)
    endif()
endif()

if(ANEM_ERR_LOG)
    target_compile_definitions(nem PUBLIC NEM_ERR_LOG)
endif()

if(ANEM_HIGH_PRECISION)
    target_compile_definitions(nem PUBLIC NEM_USE_DOUBLE_PRECISION)
endif()