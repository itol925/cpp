cmake_minimum_required(VERSION 3.5)
project(test/continuable)

add_executable(continuable-demo continuable.cpp)

target_include_directories(continuable-demo PRIVATE ../../third-party/asio/include)
target_include_directories(continuable-demo PRIVATE ../../third-party/continuable/include)
target_include_directories(continuable-demo PRIVATE ../../third-party/function2/function2/include)

target_link_libraries(continuable-demo gtest-main)
gtest_discover_tests(continuable-demo)