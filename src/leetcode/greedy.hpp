#include <iostream>
#include <vector>
#include <numeric>

/**
* 贪心算法
* 每次操作都是局部最优，使得最终整体最优。
*/
namespace leetcode::greedy {
    namespace assign_cookies {
        /** Easy
        * 有一群孩子和一堆饼干，每个孩子有一个饥饿度，每个饼干都有一个大小。
        * 每个孩子只能吃一个饼干，只有饼干的大小不小于孩子的饥饿度时，这个孩子才能吃饱。
        * 求解最多有多少孩子可以吃饱。
        *
        * step1: 给孩子和饼干按从小到大排序
        * step2: 遍历。从最小的孩子开始选饼干
        */
        int assign_cookies(std::vector<int> children, std::vector<int> cookies) {
            std::sort(children.begin(), children.end());
            std::sort(cookies.begin(), cookies.end());

            int child = 0;
            int cookie = 0;
            while (child < children.size() && cookie < cookies.size()) {
                if (children[child] <= cookies[cookie]) {
                    ++child;
                }
                ++cookie;
            }
            return child;
        }
        void test() {
            std::vector<int> children = {1, 3, 2};
            std::vector<int> cookies = {1, 2, 2};
            std::cout << "assign_cookies，可以喂饱孩子个数:" << assign_cookies(children, cookies) << std::endl;
        }
    }
    namespace candy {
        /** Hard
        * 一群孩子站成一排，每一个孩子有自己的评分。
        * 现在需要给这些孩子发糖果，规则是如果一个孩子的评分比自己身旁的一个孩子要高，
        * 那么这个孩子就必须得到比身旁孩子更多的糖果。孩子至少要有一个糖果。
        * 求解最少需要多少个糖果。
        *
        * step1: 孩子初始化为1
        * step2: 从左往右遍历，如果右边孩子评分比左边高，则右边孩子+1
        * step3：从右往左遍历，如果左边孩子评分比右边高，则左边孩子+1
        */
        int candy(std::vector<int> children, std::vector<int> cookies) {
            for (int i = 0; i < children.size() - 1; ++i) {
                if (children[i] > children[i + 1]) {
                    cookies[i] =  cookies[i + 1] + 1;
                }
            }
            for (int i = children.size() - 1; i > 1; --i) {
                if (children[i] > children[i - 1]) {
                    cookies[i] = cookies[i - 1] + 1;
                }
            }
            return std::accumulate(cookies.begin(), cookies.end(), 0);

        }
        void test() {
            std::vector<int> children = {1, 0, 2};
            std::vector<int> cookies = {1, 1, 1};
            std::cout << "candy. cookie:" << candy(children, cookies) << std::endl;
        }
    }

    namespace eraseOverlapIntervals {
        /**
         * 指定多个区间，计算让这些区间互不重叠的需要移除区间的最小个数，起止相连不算重叠
         * 比如：input 为 [[1, 2], [2, 4], [1, 3]]，输出 [[1, 2], 2, 4]]
         *
         * step1: 按数组首个数字排序
         * step2: 遍历移除重叠区域
         */
        int eraseOverlapIntervals(std::vector<std::vector<int>> &areas) {
            std::sort(areas.begin(), areas.end(), [](std::vector<int>& a, std::vector<int>& b) {
                return a[0] < b[0];
            });

            int removes = 0;
            std::vector<int> intervals = areas[0];
            for (int i = 1; i < areas.size(); ++i) {
                if (areas[i][0] < intervals[1]) {
                    removes++;
                } else {
                    intervals = areas[i];
                }
            }
            return removes;
        }

        void test() {
            std::vector<std::vector<int>> areas = {{1, 2}, {2, 4}, {1, 3}};
            int removes = eraseOverlapIntervals(areas);
            std::cout << "eraseOverlapIntervals. remove:" << removes;
        }
    }
}