cmake_minimum_required(VERSION 3.5)
project(test/boost)

## boost 库
set(BOOST_ROOT "/opt/homebrew")
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories("/usr/local/include")

add_executable(boost boost.cpp)
target_link_libraries(boost gtest_main)

gtest_discover_tests(boost)