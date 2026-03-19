add_library(nem STATIC 
    src/nem.cpp
    include/nem.hpp
    include/utils.hpp
    include/vec.hpp
)

target_include_directories(nem PUBLIC include)
set_target_properties(nem PROPERTIES FOLDER "Library")