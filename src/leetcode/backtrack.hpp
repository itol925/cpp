#include <vector>
#include <iostream>
#include "common/common.hpp"

namespace leetcode {
    namespace backtrack {
        using namespace std;
        using common::array_to_string;
        namespace permutations {
           /**
            * 排列回溯
            * 输入一个数组，输出一个二维数组，为数组的所有排列组合
            * eg. input:[1,2,3], output:[[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 2, 1], [3, 1, 2]]
            */
            void dfs(vector<vector<int>> &ans, vector<int> &arr, int level) {
                if (level == arr.size() - 1) {
                    ans.push_back(arr);
                    return;
                }
                for (int i = level; i < arr.size(); ++i) {
                    swap(arr[i], arr[level]);
                    dfs(ans, arr, level + 1);
                    swap(arr[i], arr[level]);
                }
            }
            vector<vector<int>> permutation(vector<int> arr) {
                vector<vector<int>> ans;
                dfs(ans, arr, 0);
                return ans;
            }
            void test() {
                cout << "排列回溯 permutations:" << array_to_string(permutation({1, 2, 3})) << endl;
            }
        }

        namespace combinations {
           /**
            * 组合回溯
            * 给定一个整数n和一个整数k，求在1到n中选取k个数字的所有组合方法
            * 排列是交换位置后再回溯，组合是重置“是否添加当前数字到结果中”的标识位后回溯
            * eg. input: n=4,k=2. output:[[1,2],[1,3],[1,4],[2,3]...]
            */
            void dfs(vector<vector<int>> &ans, vector<int> &comb, int &count, int n, int k, int pos) {
                if (count == k) {
                    ans.push_back(comb);
                    return;
                }
                for (int i = pos; i <= n; i++) {
                    comb[count++] = i; // comb 赋值
                    dfs(ans, comb, count, n, k, i+1);
                    --count;
                }
            }
            vector<vector<int>> combination(int n, int k) {
                vector<vector<int>> ans; // 组合后的数组
                vector<int> comb(k, 0); // 组合后的数组元素
                int count = 0; // comb数组的元素个数
                dfs(ans, comb, count, n, k, 1);
                return ans;
            }

            void test() {
                cout << "组合回溯 combinations:" << array_to_string(combination(4,2)) << endl;
            }

        }

        namespace word_search {
            /*
             * 给定一个二维字母矩阵，所有字母都与上下左右四个方向的字母相连
             * 输入一个字母矩阵和一个字符串，输出一个布尔值，表示字符串能否被寻找到
             */
            bool dfs(vector<vector<char>> &board, vector<vector<bool>> visited, string &word, string &target, int r, int c) {
                if (word.size() >= target.size() || board[r][c] != target[word.size()]) {
                    return false;
                }
                if (visited[r][c]) {
                    return false;
                }
                word += board[r][c];
                cout << "(" << r << "," << c << "),";
                visited[r][c] = true;
                if (word == target) {
                    return true;
                }

                bool ret = false;
                if (r < board.size() - 1) { // right
                    ret = dfs(board, visited, word, target, r + 1, c);
                }
                if (!ret && r > 0) { // left
                    ret = dfs(board, visited, word, target, r - 1, c);
                }
                if (!ret && c < board[r].size() - 1) { // down
                    ret = dfs(board, visited, word, target, r, c + 1);
                }
                if (!ret && c > 0) { // up
                    ret  = dfs(board, visited, word, target, r, c - 1);
                }
                return ret;
            }
            bool word_search(vector<vector<char>> &board, string &target) {
                string word = "";
                vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
                bool ret = dfs(board, visited, word, target, 0, 0);
                cout << "word_search:" << ret << endl;
            }
            void test() {
                vector<vector<char>> board = {
                        {'A', 'B', 'C', 'E'},
                        {'S', 'F', 'C', 'S'},
                        {'A', 'D', 'E', 'E'}
                };
                string target = "ABFSA";
                word_search(board, target);
            }
        }
    }
}