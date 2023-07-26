cmake_minimum_required(VERSION 3.5)

project(src/base LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines-ts")

set(src
        src/base/initialization.hpp
        src/base/storage.hpp
        src/base/function.hpp
        src/base/coroutine.hpp
        src/base/classes.hpp
        src/base/segment.hpp

        src/boost/io.hpp
    )

set(BOOST_ROOT "/opt/homebrew")
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

ADD_EXECUTABLE(test main.cpp ${src})
set_target_properties(test PROPERTIES LINKER_LANGUAGE CXX)
