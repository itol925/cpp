cmake_minimum_required(VERSION 3.5)

project(base LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines-ts")

set(src
        src/initialization.hpp
        src/storage.hpp
        src/function.hpp
        src/coroutine.hpp
    )

ADD_EXECUTABLE(base main.cpp ${src})
set_target_properties(base PROPERTIES LINKER_LANGUAGE CXX)
