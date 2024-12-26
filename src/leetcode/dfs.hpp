#include <iostream>
#include <vector>
#include <stack>
#include <numeric>

using namespace std;

/**
 * 深度优先搜索 deep-first-search
 */
namespace leetcode::dfs {
    /**
     * 给定一个二维0-1矩阵，0表示海洋，1表示陆地，每个格子只能与上下左右相邻，求最大岛屿面积
     */
    namespace max_area_of_island {
        int val(vector <vector<int>> &island, int r, int c) {
            if (r > island.size() - 1 || r < 0 || c > island[0].size() - 1 || c < 0) {
                return 0;
            }
            if (island[r][c] == 0) {
                return 0;
            }
            int area = 1;
            island[r][c] = 0;
            // up
            area += val(island, r - 1, c);
            // down
            area += val(island, r + 1, c);
            // left
            area += val(island, r, c - 1);
            // right
            area += val(island, r, c + 1);
            return area;
        }

        void test() {
            std::vector <std::vector<int>> island = {
                    {1, 0, 1, 0, 1, 1, 0},
                    {1, 1, 1, 0, 1, 1, 0},
                    {0, 0, 0, 0, 1, 1, 1}
            };
            int area = 0;
            for (int r = 0; r < island.size(); r++) {
                for (int c = 0; c < island[0].size(); c++) {
                    area = max(area, val(island, r, c));
                }
            }
            cout << "max area of island:" << area << endl;
        }

        // 通过 stack 实现
        int val2(vector <vector<int>> &island) {
            int maxArea = 0;
            for (int r = 0; r < island.size(); ++r) {
                for (int c = 0; c < island[0].size(); ++c) {
                    if (island[r][c] > 0) {
                        std::stack <std::vector<int>> st;
                        int area = 0;
                        st.push({r, c});
                        island[r][c] = 0;
                        while (!st.empty()) {
                            std::vector<int> p = st.top();
                            st.pop();
                            area++;
                            if (p[0] > 0 && island[p[0] - 1][p[1]] > 0) {
                                st.push({p[0] - 1, p[1]});
                                island[p[0] - 1][p[1]] = 0;
                            }
                            // down
                            if (p[0] < island.size() - 1 && island[p[0] + 1][p[1]] > 0) {
                                st.push({p[0] + 1, p[1]});
                                island[p[0] + 1][p[1]] = 0;
                            }
                            // left
                            if (p[1] > 0 && island[p[0]][p[1] - 1] > 0) {
                                st.push({p[0], p[1] - 1});
                                island[p[0]][p[1] - 1] = 0;
                            }
                            // right
                            if (p[1] < island[0].size() - 1 && island[p[0]][p[1] + 1] > 0) {
                                st.push({p[0], p[1] + 1});
                                island[p[0]][p[1] + 1] = 0;
                            }
                        }
                        maxArea = std::max(maxArea, area);
                    }
                }
            }
            return maxArea;
        }

        void test2() {
            std::vector <std::vector<int>> island = {
                    {1, 0, 1, 0, 1, 1, 0},
                    {1, 1, 1, 1, 1, 1, 0},
                    {0, 0, 0, 0, 1, 1, 1}
            };
            cout << "max area of island2:" << val2(island) << endl;
        }
    }

    namespace friend_circle {
        /**
         * 给定一个二维0-矩阵，第（i,j）是位置1，表示第i个人和第j个人是朋友，朋友的关系是可传递的，如果a和b是朋友，b和c是朋友，那a和c也是朋友。
         * 问一共有多少个朋友圈.
         * 如下图：第(1, 0)为1，表示第1个人和第0个人是朋友，对角线必定是1因为自己和自己必定是朋友
         */
        int dfs(vector<vector<int>> &fc, int r, int c) {
            if (r > fc.size() -1 || r < 0 || c > fc[0].size() - 1 || c < 0) {
                return 0;
            }
            if (!fc[r][c]) {
                 return 0;
            }
            fc[r][c] = 0;
            int val = 1;
            val += dfs(fc, r + 1, c);
            val += dfs(fc, r - 1, c);
            val += dfs(fc, r, c + 1);
            val += dfs(fc, r, c - 1);
            return val;
        }
        void test() {
            vector<vector<int>> fc = {
                    {1, 1, 0},
                    {1, 1, 0},
                    {0, 0, 1}
            };
            int count = 0;
            for (int i = 0; i < fc.size(); i++) {
                for (int j = 0; j < fc[0].size(); j++) {
                    int val = dfs(fc, i, j);
                    if (val > 0) {
                        count++;
                        cout << "fc:" << val << endl;
                    }
                }
            }
            cout << "朋友圈数：" << count << endl;
        }
    }
}