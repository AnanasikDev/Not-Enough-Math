add_executable(tests main.cpp)

target_link_libraries(tests 
    PRIVATE 
        nem 
        Catch2::Catch2WithMain
)

include(Catch) # makes tests show up in Visual Studio's Test Explorer
catch_discover_tests(tests)

set_target_properties(tests PROPERTIES FOLDER "Tests")
