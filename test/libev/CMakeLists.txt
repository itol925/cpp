cmake_minimum_required(VERSION 3.5)
project(test/libev)

# ev 库
find_library(LIBEV_LIBRARY NAMES ev)
if(NOT LIBEV_LIBRARY)
    message(FATAL_ERROR "LIBEV_LIBRARY not found")
endif()
include_directories ("/opt/homebrew/include")

add_executable(libev-demo libev.cpp)
target_link_libraries(libev-demo ${LIBEV_LIBRARY})
target_link_libraries(libev-demo gtest-main)
gtest_discover_tests(libev-demo)