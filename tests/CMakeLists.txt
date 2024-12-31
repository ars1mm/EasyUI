add_executable(test_window test_window.c)
target_link_libraries(test_window PRIVATE easyui)
add_test(NAME test_window COMMAND test_window)
