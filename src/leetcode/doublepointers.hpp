#include <vector>
#include <iostream>
#include "common/common.hpp"
using namespace std;
using common::array_to_string;
/**
 * 双指针
 * 双指针主要用于遍历数组，两个指针指向不同的元素，协同完成任务
 * 若两个指针指向同一数组，遍历同一方向且不相交，则称为 滑动窗口，遍历相反方向，则一般用来搜索（目标数组往往是排好序的）
 */
namespace leetcode::double_pointers {
    namespace two_sum {
        /** 两数相加
         * Easy
         * 给定一个增序的数组，找到2个数，使其和为定值。已知只有一对解
         *
         * step1: 两个指针一个指向头，一个指向尾，分别向中间移动
         */
        std::vector<int> two_sum(std::vector<int> arr, int target) {
            int l = 0;
            int r = arr.size() - 1;
            while (r > l) {
                int sum = arr[l] + arr[r];
                if (sum == target) {
                    return {arr[l], arr[r]};
                } else if (sum < target) {
                    l++;
                } else {
                    r--;
                }
            }
            return {-1};
        }

        void test() {
            vector<int> arr = {1, 3, 6, 7, 9};
            int target = 10;
            cout << "two sum = " << target << ":" << array_to_string(two_sum(arr, target)) << endl;
        }
    }

    namespace merge_sort_arr {
        /** Easy
         * 归并有序数组
         * 给定两个有序数组，将其合二为一，要求不开辟新的内存，target数组长度为m，merge数组长度为n
         * 将target数组长度延长到m+n,多出的元素以0补齐
         */
        void merge_sort_arr(vector<int> &target, vector<int> &merge, int m, int n) {
            int p = target.size() - 1;
            m--, n--;
            for (int i = target.size() - 1; i >= 0; i--) { // 从后往前向 arr1 补数
                if (m < 0) {
                    target[i] = merge[n];
                    n--;
                    continue;
                }
                if (n < 0) {
                    target[i] = target[m];
                    m--;
                    continue;
                }
                if (target[m] > merge[n]) {
                    target[i] = target[m];
                    m--;
                } else {
                    target[i] = merge[n];
                    n--;
                }
            }
        }

        void test() {
            vector<int> target = {2, 4, 5, 7, 0, 0, 0};
            vector<int> merge = {1, 6, 12};
            merge_sort_arr(target, merge, 4, 3);
            cout << "merge two arr:" << array_to_string(target) << endl;
        }
    }

    namespace minimum_window_substring {
        /**
         * 滑动窗口
         *
         */
    }
}