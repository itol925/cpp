#include <vector>
#include <iostream>
#include "common/common.hpp"
using namespace std;
using common::array_to_string;
/**
 * 动态规划
 * 将问题拆分成多个子问题，为避免重复计算，子问题的结果被保存。
*/

namespace leetcode {
    namespace dynamic_programming {
        namespace climbing_stairs {
            /**
             * 给定n个台阶，每次可以走一步或走两步，求一共有多少种方式可以走完这些台阶
             * 输入n表示台阶的数量，输出所有的方式。
             * 如输入3，输出3[[1,1,1],[1,2][2,1]]
             * 思路：
             * 当n=1时，有1种方式
             * 当n=2时，有2种方式
             * 当n=3时，有3种方式
             * 当n=4时，有5种方式
             * 即斐波那契数列，即走完n阶台阶的方式 = 走完n-1阶台阶的方式 + 走完n-2阶台阶的方式
             */
            int climbing(int n) {
                if (n == 1) return 1;
                if (n == 2) return 2;
                return climbing(n - 1) + climbing(n - 2);
            }
            void test() {
                cout << "ret:" << climbing(4) << endl;
            }
        }

        namespace house_robber {
            /**
             * 假如你是一个劫匪，决定抢一条街的房子，每个房子内的钱数不同，如果抢了两栋相邻的房子则会触发报警，求在不触发报警的情况下最多可以抢多少钱
             * 输入[2，7，9，3，1]，输出12，即抢第1，3，5家钱最多
             *
             * 思路
             * 当到第i家时，可以选择抢或不抢，如果抢，则收益=sum[i-2] + num[i]，如果不抢，则收益=sum[i-1]
             * 所以，收益=max(sum[i-2] + num[i], sum[i-1])
             */

            // 返回抢到第i家时最大的收益
            int house_robber(vector<int> &nums, int i) {
                if (i == 0) return nums[i];
                if (i == 1) return std::max(nums[0], nums[1]);
                if (i == 2) return std::max(nums[0] + nums[2], nums[1]);
                return std::max(house_robber(nums, i - 2) + nums[i], house_robber(nums, i - 1));
            }

            int house_robber2(vector<int> &nums) {
                vector<int> sum(nums.size(), 0);
                sum[0] = nums[0];
                sum[1] = std::max(nums[0], nums[1]);
                for (int i = 2; i < nums.size(); i++) {
                    sum[i] = std::max(sum[i-1], sum[i-2] + nums[i]);
                }
                return sum[nums.size() - 1];
            }

            void test() {
                vector<int> nums = {2,7,9,3,1,3};
                cout << "res:" << house_robber(nums, nums.size() - 1) << endl;
                cout << "res2:" << house_robber2(nums) << endl;
            }
        }

        namespace arithmetic_slices {
            /**
             * 给定一个数组，求这个数组中连续且等差的子数组一共有多少个
             * 如：input：[1，2，3，4], output:3。分别是[1,2,3],[2,3,4],[1,2,3,4]
             * 思路：
             * f(i)表示第i个数字结尾的等差数列个数。f(i)=f(i-1)+1. todo：这个等式还没理解
             * f(1) = f(2) = 0;
             * f(3) = f(2) + 1 = 1
             * f(4) = f(3) + 1 = 2
             * f(5) = f(4) + 1 = 3
             * f(6) = f(5) + 1 = 4
             */
            int arithmetic_slices(vector<int> &arr) {
                if (arr.size() < 3) {
                    return 0;
                }
                vector<int> res(arr.size(), 0);
                for (int i = 2; i < arr.size(); i++) {
                    if (arr[i] - arr[i-1] == arr[i-1] - arr[i-2]) {
                        res[i] = res[i-1] + 1;
                    }
                }
                return accumulate(res.begin(), res.end(), 0);
            }
             int arithmetic_slices2(vector<int> &arr) {
                 if (arr.size() < 3) {
                     return 0;
                 }
                 int count = 0;
                 int add = 1;
                 for (int i = 2; i < arr.size(); i++) {
                     if (arr[i] - arr[i-1] == arr[i-1] - arr[i-2]) {
                         count += add++;
                     } else {
                         add = 1;
                     }
                 }
                 return count;
             }

             void test() {
                 vector<int> arr = {1,2,3,4,5,6};
                 cout << "res：" << arithmetic_slices(arr) << endl;
                 cout << "res2：" << arithmetic_slices2(arr) << endl;
             }
        }

        namespace min_path_sum {
            /**
             * 给定一个MxN大小的非负整数矩阵，求从左上角开始到右下角结束的，经过的数字的最小路径，每次只能向右或者向下移动
             * 思路：sum[i][j] = min(sum[i-1][j] + grid[i][j], sum[i][j-1] + grid[i][j])
             */
            int min_path_sum(vector<vector<int>> &grid) {
                vector<vector<int>> sum(grid.size(), vector(grid[0].size(), 0));
                sum[0][0] = grid[0][0];
                for (int i = 0; i < grid.size(); i++) {
                    for (int j = 0; j < grid[0].size(); j++) {
                        if (i == 0 && j == 0) {
                            sum[i][j] = grid[i][j];
                        } else if (i == 0) {
                            sum[i][j] = sum[i][j-1] + grid[i][j];
                        } else if (j == 0) {
                            sum[i][j] = sum[i-1][j] + grid[i][j];
                        } else {
                            sum[i][j] = std::min(sum[i-1][j], sum[i][j-1]) + grid[i][j];
                        }
                    }
                }
                //cout << "grid:" << array_to_string(sum) << endl;
                return sum[grid.size()-1][grid[0].size()-1];
            }
            void test() {
                vector<vector<int>> grid = {
                        {1,3,1},
                        {1,5,1},
                        {4,2,1}
                };
                cout << "res:" << min_path_sum(grid) << endl;
            }
        }

        namespace matrix_01 {
            /**
             * 给定一个由01组成的二维矩阵，求每个位置到最近的0的距离
             * 输入一个二维01数组，输出一个同样大小的二维数组，表示每个位置到最近的0的距离
             * 思路：往一个方向遍历（左上向右下遍历，或者右下往左上遍历），dis（i,j）= 上一个位置+1 或 当前值
             */
             vector<vector<int>> matrix_01(vector<vector<int>> &grid) {
                vector<vector<int>> dist(grid.size(), vector<int>(grid[0].size(), INT_MAX - 1));
                // 左上往右下搜索
                for (int i = 0; i < grid.size(); i++) {
                    for (int j = 0; j < grid[0].size(); j++) {
                        if (grid[i][j] == 0) {
                            dist[i][j] = 0;
                        } else {
                            if (j > 0) {
                                dist[i][j] = min(dist[i][j], dist[i][j-1] + 1);
                            }
                            if (i > 0) {
                                dist[i][j] = min(dist[i][j], dist[i-1][j] + 1);
                            }
                        }
                    }
                }
                // 右下往左上搜索
                for (int i = grid.size() - 1; i >= 0; i--) {
                    for (int j = grid[0].size() - 1; j >= 0; j--) {
                        if (grid[i][j] == 0) {
                            dist[i][j] = 0;
                        } else {
                            if (i < grid.size() - 1) {
                                dist[i][j] = min(dist[i][j], dist[i+1][j] + 1);
                            }
                            if (j < grid[0].size() - 1) {
                                dist[i][j] = min(dist[i][j], dist[i][j+1] + 1);
                            }
                        }
                    }
                }
                return dist;
             }
             void test() {
                 vector<vector<int>> grid = {
                         {0,0,0},
                         {0,1,0},
                         {1,1,1}
                 };
                 auto res = matrix_01(grid);
                 cout << "res:" << array_to_string(res) << endl;
             }
        }

        namespace maximal_square {
            /**
             * 给定一个01矩阵，求全由1构成的正方形面积
             * 思路：
             * 当 grid[i][j]=1时，如果grid[i-1][j] = grid[i][j-1] = grid[i-1][j-1] = 1时，
             * area[i][j]=min(area[i-1][j], area[i][j-1], area[i-1][j-1]) + 1,
             */
             int maximal_square(vector<vector<int>> &grid) {
                 vector<vector<int>> area(grid.size(), vector<int>(grid[0].size(), 0));
                 int max_size = 0;
                 for (int i = 1; i < grid.size(); i++) {
                     for (int j = 1; j < grid[0].size(); j++) {
                         if (grid[i][j] == 1) {
                             area[i][j] = min(area[i-1][j-1], min(area[i-1][j], area[i][j-1])) + 1;
                         }
                         max_size = max(max_size, area[i][j]);
                     }
                 }
                 return max_size * max_size;
             }
             void test() {
                 vector<vector<int>> grid = {
                         {0,0,1,0},
                         {0,1,1,1},
                         {1,1,1,1},
                         {0,1,1,1},
                 };
                 cout << "res:" << maximal_square(grid) << endl;
             }
        }

        namespace perfect_squares {
            /**
             * 给定一个正整数n，求和为n的完全平方数的最少数量
             * 比如：n=13 = 2^2+4^2 = 4+9，需要2个数的平方和，返回2
             * 注：每个数都有，最差的的情况比如4=1^2 + 1^2 + 1^2 + 1^2，返回4
             * 思路：
             * 定义一个一维矩阵dp，其中dp[i]表示数字i最少可以由几个完全平方数相加构成，其中位置i只依赖i-k^2的位置，如i-4, i-9等，
             * 才能满足完全平方分割的条件
             */
            int perfect_squares(int n) {
                vector<int> dp(n+1, INT32_MAX);
                dp[0] = 0;
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j * j <= i; j++) {
                        dp[i] = min(dp[i], dp[i-j*j] + 1);
                    }
                }
                return dp[n];
            }
            void test() {
                int n = 13;
                cout << "perfect_squares n=" << n << ", ret=" << perfect_squares(n) << endl;
            }
        }

        namespace decode_ways {
            /**
             * 已知字母A-Z可以表示成1-26，给定一个数字串，求有多少种不同的字符串等价于这个字符串
             * 比如 input:226，output:3，有 BZ(2, 26)、VF(22,6)、BBF(2,2,6) 三种方式
             * 思路：
             * 对于字符串 s 的某个位置 i 而言，我们只关心「位置 i 自己能否形成独立 item 」和「位置 i 能够与上一位置（i-1）能否形成 item」，
             * 而不关心 i-1 之前的位置。
             *
             * 有了以上分析，我们可以从前往后处理字符串 s，使用一个数组记录以字符串 s 的每一位作为结尾的解码方案数。即定义 f[i] 为考虑前 i 个字符的解码方案数。
             * 对于字符串 s 的任意位置 i 而言，其存在三种情况：
             * 1）只能由位置 i 的单独作为一个 item，设为 a，转移的前提是 a 的数值范围为 [1,9]，转移逻辑为 f[i]=f[i−1]。
             * 2）只能由位置 i 的与前一位置（i-1）共同作为一个 item，设为 b，转移的前提是 b 的数值范围为 [10,26]，转移逻辑为 f[i]=f[i−2]。
             * 3）位置 i 既能作为独立 item 也能与上一位置形成 item，转移逻辑为 f[i]=f[i−1]+f[i−2]。
             */


        }
    }
}