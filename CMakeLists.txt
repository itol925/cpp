cmake_minimum_required(VERSION 3.5)

project(src/stl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines-ts")

set(src
        src/stl/initialization.hpp
        src/stl/storage.hpp
        src/stl/function.hpp
        src/stl/coroutine.hpp
        src/stl/classes.hpp
        src/stl/segment.hpp
        src/stl/overload.hpp
        src/stl/template.hpp
        src/stl/exceptions.hpp
        src/stl/error.hpp
        src/stl/smartptr.hpp
        src/stl/chrono.hpp

        src/boost/io.hpp

        src/continuable/continuable.hpp

        src/demo/cs/common/protocol.hpp
        src/demo/cs/client/client.hpp
        src/demo/cs/server/server.hpp
        src/demo/cs/server/handler.hpp
        src/demo/cs/server/listener.hpp
        src/demo/cs/server/connection.hpp
        src/demo/cs/test.hpp
    )

set(BOOST_ROOT "/opt/homebrew")
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories ("/usr/local/include")

ADD_EXECUTABLE(test main.cpp ${src})
set_target_properties(test PROPERTIES LINKER_LANGUAGE CXX)
