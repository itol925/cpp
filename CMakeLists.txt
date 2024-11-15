cmake_minimum_required(VERSION 3.5)

project(src/stl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines-ts")

#set(src
#        src/stl/initialization.hpp
#        src/stl/storage.hpp
#        src/stl/function.hpp
#        src/stl/coroutine.hpp
#        src/stl/classes.hpp
#        src/stl/segment.hpp
#        src/stl/overload.hpp
#        src/stl/template.hpp
#        src/stl/exceptions.hpp
#        src/stl/error.hpp
#        src/stl/smartptr.hpp
#        src/stl/chrono.hpp
#        src/stl/ref.hpp
#        src/stl/tools.hpp
#        src/stl/ptr.hpp
#        src/stl/condition.hpp
#        src/stl/noncopyable.hpp
#        src/stl/promise.hpp
#        src/stl/member.hpp
#
#        src/common/common.hpp
#
#        src/demo/cs/common/protocol.hpp
#        src/demo/cs/client/client.hpp
#        src/demo/cs/server/server.hpp
#        src/demo/cs/server/handler.hpp
#        src/demo/cs/server/listener.hpp
#        src/demo/cs/server/connection.hpp
#        src/demo/cs/test.hpp
#        src/demo/transaction/transaction.hpp
#
#        src/leetcode/test1.hpp
#        src/leetcode/sort.hpp
#        src/leetcode/greedy.hpp
#        src/leetcode/doublepointers.hpp
#        src/leetcode/research.hpp
#
#        src/io/libev.hpp
#    )
#
## ev 库
#find_library(LIBEV_LIBRARY NAMES ev)
#if(NOT LIBEV_LIBRARY)
#    message(FATAL_ERROR "LIBEV_LIBRARY not found")
#endif()
#

#
include_directories(src)

#
#ADD_EXECUTABLE(test main.cpp ${src})
#set_target_properties(test PROPERTIES LINKER_LANGUAGE CXX)
#target_link_libraries(test ${LIBEV_LIBRARY})

# FetchContent 是 CMake 的一个模块，用于在项目构建过程中自动下载和集成外部项目或库
include(FetchContent)

# FetchContent_Declare 用于声明一个要获取的外部内容。在此处，我们定义了 googletest 项目，并指定了 Google Test 源代码的下载 URL
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# FetchContent_MakeAvailable 用于执行刚才声明的外部项目的下载和添加。这行代码会在构建时下载并准备好 googletest，之后我们就可以在项目中使用它了。
FetchContent_MakeAvailable(googletest)

# CMake 内置命令，用于启用测试功能。启用后，CMake 将添加 CTest 支持，允许我们定义和运行测试
enable_testing()
include(GoogleTest)

add_subdirectory(test/hello)
add_subdirectory(test/asio)