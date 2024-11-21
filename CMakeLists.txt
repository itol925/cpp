cmake_minimum_required(VERSION 3.5)

project(src/stl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines-ts")
add_compile_options(-Wno-deprecated-declarations)

include_directories(src)
include_directories(third-party/googletest)
add_subdirectory(third-party/googletest)

# CMake 内置命令，用于启用测试功能。启用后，CMake 将添加 CTest 支持，允许我们定义和运行测试
enable_testing()
include(GoogleTest)

add_subdirectory(test/hello)
add_subdirectory(test/asio)
add_subdirectory(test/continuable)
add_subdirectory(test/demo)
add_subdirectory(test/libev)