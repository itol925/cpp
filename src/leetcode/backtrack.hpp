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
                    comb[count++] = i;
                    dfs(ans, comb, count, n, k, i+1);
                    --count;
                }
            }
            vector<vector<int>> combination(int n, int k) {
                vector<vector<int>> ans;
                vector<int> comb(k, 0);
                int count = 0;
                dfs(ans, comb, count, n, k, 1);
                return ans;
            }

            void test() {
                cout << "组合回溯 combinations:" << array_to_string(combination(4,2)) << endl;
            }

        }
    }
}