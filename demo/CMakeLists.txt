add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE nem)
set_target_properties(demo PROPERTIES FOLDER "Apps")