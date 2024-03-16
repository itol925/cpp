#include <vector>
#include <iostream>

namespace leetcode {
    /**
     * 双指针
     * 双指针主要用于遍历数组，两个指针指向不同的元素，协同完成任务
     * 若两个指针指向同一数组，遍历同一方向且不相交，则称为 滑动窗口，遍历相反方向，则一般用来搜索（目标数组往往是排好序的）
     */
    namespace doublepointers {
        /**
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

        void test() {
            twoSum();
        }
    }
}