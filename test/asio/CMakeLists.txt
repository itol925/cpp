cmake_minimum_required(VERSION 3.5)
project(test/asio)

include(FetchContent)

# 引入独立的 Asio 库
FetchContent_Declare(
        asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG asio-1-24-0  # 指定所需版本（可选）
)
# 下载并添加 Asio 库
FetchContent_MakeAvailable(asio)

add_executable(asio asio.cpp)
# 创建可执行文件并包含 Asio 头文件路径
target_include_directories(asio PRIVATE ${asio_SOURCE_DIR}/asio/include)

# link gtest
target_link_libraries(asio gtest_main)
gtest_discover_tests(asio)