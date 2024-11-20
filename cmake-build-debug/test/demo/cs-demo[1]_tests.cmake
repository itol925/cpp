add_test([=[Demo.CS]=]  /Users/panyinglong/workspace/cpp/cmake-build-debug/test/demo/cs-demo [==[--gtest_filter=Demo.CS]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Demo.CS]=]  PROPERTIES WORKING_DIRECTORY /Users/panyinglong/workspace/cpp/cmake-build-debug/test/demo SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  cs-demo_TESTS Demo.CS)
