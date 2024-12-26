#include "gtest/gtest.h"
#include "doublepointers.hpp"
#include "greedy.hpp"
#include "research.hpp"
#include "sort.hpp"
#include "backtrack.hpp"
#include "dfs.hpp"

TEST(LeetCode, Greedy) {
    leetcode::greedy::assign_cookies::test();
}
TEST(LeetCode, Greedy2) {
    leetcode::greedy::candy::test();
}
TEST(LeetCode, Greedy3) {
    leetcode::greedy::eraseOverlapIntervals::test();
}
TEST(LeetCode, DFS) {
    leetcode::dfs::max_area_of_island::test();
    leetcode::dfs::max_area_of_island::test2();
}
TEST(LeetCode, DFS2) {
    leetcode::dfs::friend_circle::test();
}

TEST(LeetCode, Backtrack) {
    leetcode::dfs::backtrack::permutations::test();
}
TEST(LeetCode, Backtrack2) {
    leetcode::dfs::backtrack::combinations::test();
}
TEST(LeetCode, Backtrack3) {
    leetcode::dfs::backtrack::word_search::test();
}
TEST(LeetCode, Backtrack4) {
    leetcode::dfs::backtrack::n_queens::test();
}