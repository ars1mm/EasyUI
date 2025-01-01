add_executable(test_window test_window.c)
target_link_libraries(test_window PRIVATE easyui)

if(CI_BUILD)
    target_compile_definitions(test_window PRIVATE CI_BUILD)
endif()

add_test(NAME test_window COMMAND test_window)
