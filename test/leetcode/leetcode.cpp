#include "gtest/gtest.h"
#include "doublepointers.hpp"
#include "greedy.hpp"
#include "research.hpp"
#include "sort.hpp"
#include "backtrack.hpp"

TEST(LeetCode, Backtrack) {
    leetcode::backtrack::permutations::test();
    leetcode::backtrack::combinations::test();
}