cmake_minimum_required(VERSION 3.5)
project(test/asio-demo)

# 以 INTERFACE ASIO_STANDALONE 方式编译 asio
# INTERFACE 指定目标类型为接口库，无实际产物（如静态文件）
# ASIO_STANDALONE 表示 asio 不依赖 boost，独立编译
# 注：asio 库是头文件库，因此只需要 include 头文件即可
#add_library(asio INTERFACE)
#target_compile_options(asio INTERFACE ASIO_STANDALONE)
#target_include_directories(asio INTERFACE ${ASIO_SRC})
#target_link_libraries(asio INTERFACE <threads>) # asio 依赖 threads 库

add_executable(asio-demo asio.cpp)
target_include_directories(asio-demo PRIVATE ../../third-party/asio/include)
target_link_libraries(asio-demo gtest-main)
gtest_discover_tests(asio-demo)