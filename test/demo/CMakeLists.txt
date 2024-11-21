cmake_minimum_required(VERSION 3.5)
project(test/demo)

# cs-demo
add_executable(cs-demo cs.cpp)
target_include_directories(cs-demo PRIVATE ../../third-party/asio/include)
target_include_directories(cs-demo PRIVATE ../../third-party/continuable/include)
target_include_directories(cs-demo PRIVATE ../../third-party/function2/function2/include)
target_include_directories(cs-demo PRIVATE ../../src/demo/cs)

# transaction-demo
add_executable(transaction-demo transaction.cpp)
target_include_directories(transaction-demo PRIVATE ../../src/demo/transaction)
target_link_libraries(transaction-demo gtest-main)
gtest_discover_tests(transaction-demo)