//
// Created by Yinglong Pan on 2024/11/16.
//
#include "gtest/gtest.h"
#include "continuable_demo/continuable.hpp"

TEST(Continuable, Post) {
    continuable_demo::test();
}

TEST(Continuable, TestException) {
    continuable_demo::test_exception();
}


TEST(Continuable, TestException2) {
    continuable_demo::test_exception2();
}


TEST(Continuable, Test2) {
    continuable_demo::test_with_executor();
}

TEST(Continuable, TestPromise) {
    continuable_demo::async(3).then([](int result) {
        std::cout << "result:" << result << std::endl;
    }).fail([](){
        std::cout << "failed" << std::endl;
    });
}

