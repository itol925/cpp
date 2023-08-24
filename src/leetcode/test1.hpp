#include <iostream>
#include <vector>

namespace leetcode {
    /*
     * 有一群孩子和一堆饼干，每个孩子有一个饥饿度，每个饼干都有一个大小。
     * 每个孩子只能吃 一个饼干，且只有饼干的大小不小于孩子的饥饿度时，这个孩子才能吃饱。
     * 求解最多有多少孩子 可以吃饱。
     * */
    void test_assign() {
        std::vector<int> children = {1, 2, 5, 1, 6};
        std::vector<int> cookies = {1, 2, 4, 3, 5, 2};
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
        std::cout << "count:" << child << std::endl;
    }

    /**
     * 一群孩子站成一排，每一个孩子有自己的评分。
     * 现在需要给这些孩子发糖果，规则是如果一个孩子的评分比自己身旁的一个孩子要高，
     * 那么这个孩子就必须得到比身旁孩子更多的糖果;所有孩子至少要有一个糖果。
     * 求解最少需要多少个糖果。
     */
    void test_candy() {

    }

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

    void quick_sort(std::vector<int> &nums, int l, int r) {
        if (l + 1 >= r) {
            return;
        }
        int first = l, last = r - 1, key = nums[first];
        while (first < last) {
            while (first < last && nums[last] >= key) {
                --last;
            }
            nums[first] = nums[last];
            while (first < last && nums[first] <= key) {
                ++first;
            }
            nums[last] = nums[first];
        }
        nums[first] = key;
        quick_sort(nums, l, first);
        quick_sort(nums, first + 1, r);
    }

    void test_quick_sort() {
        std::vector<int> arr = {4, 1, 3, 2, 5, 2, 8, 4};
        quick_sort(arr, 0, arr.size());
        std::cout << arr[0] << std::endl;
    }

    void test() {
        //test_candy();
        test_quick_sort();
    }
}