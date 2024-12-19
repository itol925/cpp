cmake_minimum_required(VERSION 3.5)
project(test/stl)

add_executable(stl-demo stl.cpp)
target_include_directories(stl-demo PRIVATE ../../src/stl)
target_link_libraries(stl-demo gtest-main)
gtest_discover_tests(stl-demo)