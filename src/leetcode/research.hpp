#include <iostream>
#include <vector>
#include <stack>
#include <numeric>

namespace leetcode {
    /**
     * 搜索
     */
    namespace research {
        /**
         * 给定一个二维0-1矩阵，0表示海洋，1表示陆地，求最大岛屿面积
         */
        std::vector<std::vector<int>> island = {
                {1, 0, 1, 0, 1, 1, 0},
                {1, 1, 1, 1, 1, 1, 0},
                {0, 0, 0, 0, 1, 1, 1}
        };
        int val(int r, int c) {
            if (island[r][c] == 0) {
                return 0;
            }
            int area = 1;
            island[r][c] = 0;
            // up
            if (r > 0) {
                area += val(r - 1, c);
            }
            // down
            if (r < island.size() - 1) {
                area += val(r + 1, c);
            }
            // left
            if (c > 0) {
                area += val(r, c - 1);
            }
            // right
            if (c < island[0].size() - 1) {
                area += val(r, c + 1);
            }
            return area;
        }
        // impl by recursion
        void maxAreaOfIsland() {
            int maxArea = 0;
            for (int r = 0; r < island.size(); ++r) {
                for (int c = 0; c < island[0].size(); ++c) {
                    if (island[r][c] > 0) {
                        maxArea = std::max(maxArea, val(r, c));
                    }
                }
            }
            std::cout << "max:" << maxArea << std::endl;
        }

        // impl by stack
        void maxAreaOfIsland2() {
            int maxArea = 0;
            for (int r = 0; r < island.size(); ++r) {
                for (int c = 0; c < island[0].size(); ++c) {
                    if (island[r][c] > 0) {
                        std::stack<std::vector<int>> st;
                        int area = 0;
                        st.push({r, c});
                        island[r][c] = 0;
                        while (!st.empty()) {
                            std::vector<int> p = st.top();
                            st.pop();
                            area++;
                            std::cout << "[" << p[0] << "," << p[1] << "]" << std::endl;
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
            std::cout << "max:" << maxArea << std::endl;
        }


        /**
         * 给定一个二维0-矩阵，第（i,j）是位置1，表示第i个人和第j个人是朋友，朋友的关系是可传递的，如果a和b是朋友，b和c是朋友，那a和c也是朋友。
         * 问一共有多少个朋友圈.
         * 如下图：第(1, 0)为1，表示第1个人和第0个人是朋友，对角线必定是1因为自己和自己必定是朋友
         */
        std::vector<std::vector<int>> fc = {
                {1, 1, 0},
                {1, 1, 0},
                {0, 0, 1}
        };
        void friendCircle() {
            for(int r = 0; r < fc.size(); r++) {
                // todo
            }
        }
        void test() {
            maxAreaOfIsland2();
        }
    }

    namespace binary_search {
        // 二分查找，针对有序数组
        int binary_search() {
            std::vector<int> arr = {1, 2, 3, 4, 5, 6};
            int target = 7;
            int l = 0, r = arr.size() - 1, mid;
            while (l < r) {
                mid = l + (r - 1) / 2;
                if (arr[l] == target) {
                    return l;
                } else if (arr[r] == target) {
                    return r;
                } else if (arr[mid] == target) {
                    return mid;
                } else {
                    if (target < arr[mid]) {
                        r = mid - 1;
                    } else {
                        l = mid + 1;
                    }
                }
            }
            return -1;
        }
    }
}