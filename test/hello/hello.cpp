//
// Created by Yinglong Pan on 2024/11/14.
//
#include "gtest/gtest.h"

TEST(HelloTest, Hello) {
EXPECT_STRNE("hello", "world");
EXPECT_EQ(7 * 6, 42);
}