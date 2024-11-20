//
// Created by Yinglong Pan on 2024/11/14.
//
#include <gtest/gtest.h>
#include "boost/io.hpp"
#include "continuable_demo/continuable.hpp"
#include "boost/threadPool.hpp"
#include "boost/promise.hpp"

TEST(BoostTest, BasicAssertions) {
    boost_demo::test_io();
    EXPECT_EQ(7 * 6, 42);
}