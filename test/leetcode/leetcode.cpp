#include "gtest/gtest.h"
#include "doublepointers.hpp"
#include "greedy.hpp"
#include "binary_search.hpp"
#include "sort.hpp"
#include "backtrack.hpp"
#include "dfs.hpp"
#include "bfs.hpp"

TEST(LeetCode, Greedy) {
    leetcode::greedy::assign_cookies::test();
}
TEST(LeetCode, Greedy2) {
    leetcode::greedy::candy::test();
}
TEST(LeetCode, Greedy3) {
    leetcode::greedy::erase_overlap_intervals::test();
}

TEST(LeetCode, DoublePoints) {
    leetcode::double_pointers::two_sum::test();
}
TEST(LeetCode, DoublePoints2) {
    leetcode::double_pointers::merge_sort_arr::test();
}
TEST(LeetCode, DoublePoints3) {
    leetcode::double_pointers::linked_list_cycle::test();
}
TEST(LeetCode, DoublePoints4) {
    leetcode::double_pointers::minimum_window_substring::test();
}

TEST(LeetCode, BinarySearch) {
    leetcode::binary_search::binary_search::test();
}
TEST(LeetCode, MySqrt) {
    leetcode::binary_search::my_sqrt::test();
}

TEST(LeetCode, InsectionSort) {
    leetcode::sort::insert_sort::test();
}
TEST(LeetCode, MergeSort) {
    leetcode::sort::merge_sort::test();
}
TEST(LeetCode, QuicSort) {
    leetcode::sort::quick_sort::test();
}
TEST(LeetCode, MaxSubArr) {
    leetcode::sort::max_sub_arr::test();
}
TEST(LeetCode, TopK) {
    leetcode::sort::topK_frequent_element::test();
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

TEST(LeetCode, BFS) {
    leetcode::bfs::shortest_bridge::test();
}
TEST(LeetCode, BFS2) {
    leetcode::bfs::word_ladder_ii::test();
}