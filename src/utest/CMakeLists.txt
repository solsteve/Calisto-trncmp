include(GoogleTest)

add_executable(FooTest trncmp_unitTest.cc)

target_link_libraries(FooTest
    callisto
    gtest
    gmock
)
gtest_add_tests(TARGET      FooTest
                TEST_LIST   noArgsTests
)
set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 10)



