cmake_minimum_required(VERSION 3.5)
project(test/asio)

#include(FetchContent)
#
#FetchContent_Declare(
#        continuable
#        GIT_REPOSITORY https://github.com/Naios/continuable.git
#        GIT_TAG 4.2.2
#)
#
#FetchContent_MakeAvailable(continuable)

add_executable(continuable continuable.cpp)
target_include_directories(continuable PRIVATE ../../third-party/continuable/include)
#
# link gtest
target_link_libraries(continuable gtest_main)
gtest_discover_tests(continuable)