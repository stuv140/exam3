set(Boost_NO_BOOST_CMAKE ON)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_executable(Mycont_tests test.cpp)

target_include_directories(Mycont_tests PRIVATE ${PROJECT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})

target_link_libraries(Mycont_tests PRIVATE ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(NAME Mycont_tests COMMAND Mycont_tests)
