#include <iostream>
#include <vector>
#include <stack>
#include <numeric>
#include "common/common.hpp"

using namespace std;
using namespace common;

/**
 * 广度优先搜索 breadth-first-search
 * 从树根起一层一层遍历
 */
namespace leetcode::bfs {
    namespace shortest_bridge {
        /**
         * 给定一个二维0-1矩阵，其中1表示陆地，0表示海洋，每个位置与上下左右相连，已知矩阵中有眀只有两个岛屿，求最少要填海造陆多少个位置才可以
         * 将两个岛屿相连.
         * 思路：找两个岛屿的最短距离
         * https://leetcode.cn/problems/shortest-bridge/description/
         */
        void bfs_find_one(vector<vector<int>> &grid, int r, int c) {
            if (r < 0 || r > grid.size() - 1 || c < 0 || c > grid[0].size() - 1) {
                return;
            }
            if (grid[r][c] == 2 || grid[r][c] == 0) {
                return;
            }
            grid[r][c] = 2;
            bfs_find_one(grid, r-1, c);
            bfs_find_one(grid, r+1, c);
            bfs_find_one(grid, r, c-1);
            bfs_find_one(grid, r, c+1);
        }

        int step_of_island(vector<vector<int>> &grid, int r, int c) {
            int step = -1;
            for (int i = r + 1; i < grid.size(); i++) { // 往下延伸
                if (grid[i][c] == 1) {
                    step = i - r;
                    break;
                }
            }
            for (int i = r - 1; i > 0; i--) { // 往上延伸
                if (grid[i][c] == 1) {
                    if (step == -1 || r - i < step) {
                        step = r - i;
                        break;
                    }
                }
            }
            for (int i = c + 1; i < grid[0].size(); i++) { // 往右延伸
                if (grid[r][i] == 1) {
                    if (step == -1 ||  i - c < step) {
                        step = i - c;
                        break;
                    }
                }
            }
            for (int i = c - 1; i > 0; i--) { // 往左延伸
                if (grid[r][i] == 1) {
                    if (step == -1 || c - i < step) {
                        step = c - i;
                        break;
                    }
                }
            }
            return step - 1;
        }
        int do_shortest_bridge(vector<vector<int>> &grid) {
            // 先找到其中一个岛屿，将值置为2
            bool find_island = false;
            for (int r = 0; r < grid.size(); r++) {
                for (int c = 0; c < grid[0].size(); c++) {
                    if (grid[r][c]) {
                        bfs_find_one(grid, r, c);
                        cout << "grid:" << array_to_string(grid) << endl;
                        find_island = true;
                        break;
                    }
                }
                if (find_island) {
                    break;
                }
            }

            // 遍历每一个值为2的点（即找到的第一个岛屿的点），不停往外延伸，直到找到值为1的点，延伸的步数即为距离
            int level = -1;
            for (int r = 0; r < grid.size(); r++) {
                for (int c = 0; c < grid[0].size(); c++) {
                    if (grid[r][c] == 2) {
                        int l = step_of_island(grid, r, c);
                        if (l > 0) {
                            if (level == -1 || l < level) {
                                level = l;
                            }
                        }
                    }
                }
            }
            return level;
        }
        void test() {
            vector<vector<int>> grid = {
                    {1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 0},
                    {1, 0, 0, 0, 0},
                    {1, 0, 0, 0, 0},
                    {1, 0, 0, 0, 1},
            };

            //vector<vector<int>> grid = {
            //        {1, 1, 1, 1},
            //        {1, 0, 0, 0},
            //        {1, 0, 0, 0},
            //        {1, 0, 0, 1},
            //};
            cout << "shortest_bridge:" << do_shortest_bridge(grid) << endl;
        }
    }
}