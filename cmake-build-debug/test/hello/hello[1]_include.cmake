if(EXISTS "/Users/panyinglong/workspace/cpp/cmake-build-debug/test/hello/hello[1]_tests.cmake")
  include("/Users/panyinglong/workspace/cpp/cmake-build-debug/test/hello/hello[1]_tests.cmake")
else()
  add_test(hello_NOT_BUILT hello_NOT_BUILT)
endif()
