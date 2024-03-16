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
        src/stl/ref.hpp
        src/stl/tools.hpp
        src/stl/ptr.hpp
        src/stl/condition.hpp
        src/stl/noncopyable.hpp
        src/stl/promise.hpp
        src/stl/member.hpp

        src/boost/io.hpp
        src/boost/threadPool.hpp
        src/boost/continuable.hpp
        src/boost/promise.hpp

        src/common/common.hpp

        src/demo/cs/common/protocol.hpp
        src/demo/cs/client/client.hpp
        src/demo/cs/server/server.hpp
        src/demo/cs/server/handler.hpp
        src/demo/cs/server/listener.hpp
        src/demo/cs/server/connection.hpp
        src/demo/cs/test.hpp
        src/demo/transaction/transaction.hpp

        src/leetcode/test1.hpp
        src/leetcode/sort.hpp
        src/leetcode/greedy.hpp
        src/leetcode/doublepointers.hpp

        src/io/libev.hpp
    )

# ev 库
find_library(LIBEV_LIBRARY NAMES ev)
if(NOT LIBEV_LIBRARY)
    message(FATAL_ERROR "LIBEV_LIBRARY not found")
endif()

# boost 库
set(BOOST_ROOT "/opt/homebrew")
find_package(Boost REQUIRED)

include_directories(src)
include_directories(${Boost_INCLUDE_DIRS})
include_directories ("/usr/local/include")

ADD_EXECUTABLE(test main.cpp ${src})
set_target_properties(test PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(test ${LIBEV_LIBRARY})
