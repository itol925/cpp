#include <vector>
#include <iostream>

namespace leetcode {
    /**
     * 双指针
     * 双指针主要用于遍历数组，两个指针指向不同的元素，协同完成任务
     * 若两个指针指向同一数组，遍历同一方向且不相交，则称为 滑动窗口，遍历相反方向，则一般用来搜索（目标数组往往是排好序的）
     */
    namespace doublepointers {
        /** 两数相加
         * Easy
         * 给定一个增序的数组，找到2个数，使其和为定值。已知只有一对解
         *
         * step1: 两个指针一个指向头，一个指向尾，分别向中间移动
         */
        void twoSum() {
            std::vector<int> arr = {2, 7, 11, 15};
            int target = 18;
            int* p1 = &arr[1];
            int* p2 = &arr[3];
            while (p2 > p1) {
                int sum = *p1 + *p2;
                if (sum == target) {
                    std::cout << "p1:" << (p1 - &arr[0]) << ", p2:" << (p2 - &arr[0]);
                    break;
                } else if (sum < target) {
                    ++p1;
                } else {
                    --p2;
                }
            }
        }

        /** Easy
         * 归并有序数组
         * 给定两个有序数组，将其合二为一，要求不开辟新的内存
         *
         * step1：从后往前依次从 arr1 和 arr2 中找最大的数，填入 arr1
         * 注：原理即 用两个指针，分别指向 arr1 和 arr2 的末尾，分别填入arr1
         */
        void mergeSortedArray() {
            std::vector<int> arr1 = {1, 2, 3, 0, 0, 0};
            std::vector<int> arr2 = {2, 5, 6}; // 将 arr2 合到 arr1 中
            int n1 = 2, n2 = 2;
            for (int i = 5; i >= 0; i--) { // 从后往前向 arr1 补数
                if (n1 < 0) {
                    arr1[i] = arr2[n2];
                    n2--;
                    continue;
                }
                if (n2 < 0) {
                    arr1[i] = arr1[n1];
                    n1--;
                    continue;
                }
                if (arr1[n1] > arr2[n2]) {
                    arr1[i] = arr1[n1];
                    n1--;
                } else {
                    arr1[i] = arr2[n2];
                    n2--;
                }
            }

            // result
            for (int i = 0; i < 6; i++) {
                std::cout << arr1[i] << ",";
            }
        }

        /**
         * 快慢指针 Medium
         * 给定一个链表，如果有环路，找出环路的开始点
         *
         */

        void test() {
            mergeSortedArray();
        }
    }
}