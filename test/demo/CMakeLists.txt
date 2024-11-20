cmake_minimum_required(VERSION 3.5)
project(test/demo)

add_executable(cs-demo cs.cpp)
target_include_directories(cs-demo PRIVATE ../../third-party/asio/include)
target_include_directories(cs-demo PRIVATE ../../third-party/continuable/include)
target_include_directories(cs-demo PRIVATE ../../third-party/function2/function2/include)

target_include_directories(cs-demo PRIVATE ../../src/demo/cs)
#target_link_libraries(cs-demo gtest-main)
#gtest_discover_tests(cs-demo)