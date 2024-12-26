#include <vector>
#include <iostream>
#include "common/common.hpp"

using namespace std;
using common::array_to_string;

/**
 * 回溯法，即深度优先算法 + 记录节点状态
 */
namespace leetcode::dfs::backtrack {

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
        /**
         * 给定一个二维字母矩阵，所有字母都与上下左右四个方向的字母相连
         * 输入一个字母矩阵和一个字符串，输出一个布尔值，表示字符串能否被寻找到
         */
        bool dfs(vector<vector<char>> &board, vector<vector<bool>> visited, string &word, int pos, int r, int c) {
            if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size()) {
                return false;
            }
            if (visited[r][c] || pos >= word.size() || word[pos] != board[r][c]) {
                return false;
            }
            cout << "(" << c << "," << r << ")->";
            if (pos == word.size() - 1) {
                return true;
            }
            visited[r][c] = true;
            bool ret = dfs(board, visited, word, pos + 1, r + 1, c); // right
            if (!ret) ret = dfs(board, visited, word, pos + 1, r - 1, c); // left
            if (!ret) ret = dfs(board, visited, word, pos + 1, r, c + 1); // down
            if (!ret) ret = dfs(board, visited, word, pos + 1, r, c - 1); // up
            visited[r][c] = false;
            return ret;
        }
        bool word_search(vector<vector<char>> &board, string &word) {
            int pos = 0;
            vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
            bool ret = dfs(board, visited, word, pos, 0, 0);
            cout << "word_search:" << ret << endl;
            return ret;
        }
        void test() {
            vector<vector<char>> board = {
                    {'A', 'B', 'C', 'E'},
                    {'S', 'E', 'C', 'S'},
                    {'A', 'D', 'E', 'E'}
            };
            string word = "ABCCES";
            word_search(board, word);
        }
    }

    namespace n_queens {
        /**
         * 给定一个大小为n的正方形国际象棋棋盘，求有多少种方式可以放置n个皇后并使得她们互相不攻击，
         * 即每一行，每一列，每一左斜行，右斜行最多只有一个皇后.
         * 注：因为一共只有n行n列，实际上每一行每一列有且仅有一个皇后。
         * 思路：每行每列建立标识数组，遍历行，回溯每种可能
         */
        bool is_safe(vector<vector<int>> &board, int n, int r, int c) {
            for (int i = 0; i < n; i++) {
                if (board[r][i] || board[i][c]) {
                    return false;
                }
            }
            for (int i = r, j = c; i < n && i >= 0 && j < n && j >= 0; i++, j++) {
                if (board[i][j]) {
                    return false;
                }
            }
            for (int i = r, j = c; i < n && i >= 0 && j < n && j >= 0; i++, j--) {
                if (board[i][j]) {
                    return false;
                }
            }
            for (int i = r, j = c; i < n && i >= 0 && j < n && j >= 0; i--, j--) {
                if (board[i][j]) {
                    return false;
                }
            }
            for (int i = r, j = c; i < n && i >= 0 && j < n && j >= 0; i--, j++) {
                if (board[i][j]) {
                    return false;
                }
            }
            return true;
        }
        bool dfs(vector<vector<int>> &board, int &count, int n, int c) {
            if (c >= n){
                count++;
                cout << "------" << endl;
                cout << array_to_string(board) << endl;
                return true;
            }

            for (int r = 0; r < n; r++) {   // 通过对每一行遍历插入 皇后 来回溯
                if (is_safe(board, n, r, c)) {  // 判断r行c列位置插入是否安全，如果安全则尝试在r行c+1列插入
                    board[r][c] = 1;
                    dfs(board, count, n, c+1);
                    board[r][c] = 0;
                }
            }
            return false;
        }
        void n_queens(int n) {
            vector<vector<int>> board(n, vector<int>(n, 0));
            int count = 0;
            dfs(board, count, n, 0);
            cout << "方案数:" << count << endl;
        }

        void test() {
            n_queens(4);
        }
    }
}