cmake_minimum_required(VERSION 3.5)
project(test/hello)

add_executable(
        hello
        hello.cpp ../boost/boost.cpp)
target_link_libraries(
        hello
        gtest_main
)

# 自动发现并注册 hello 中定义的所有 Google Test 测试用例
gtest_discover_tests(hello)