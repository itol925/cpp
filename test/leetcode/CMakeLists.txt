cmake_minimum_required(VERSION 3.5)
project(test/leetcode)

add_executable(leetcode leetcode.cpp)
target_include_directories(leetcode PRIVATE ../../src/leetcode)
target_link_libraries(leetcode gtest-main)
gtest_discover_tests(leetcode)