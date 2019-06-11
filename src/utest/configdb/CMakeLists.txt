project( configdb CXX )

add_executable(${PROJECT_NAME} ../main.cc
  utest_entry
  utest_comment
  utest_section
  utest_config
  )

target_link_libraries(${PROJECT_NAME} GTest::GTest GTest::Main callisto)
add_test(All${PROJECT_NAME}InBase ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION test
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
