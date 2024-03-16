#include <iostream>
#include <vector>

namespace leetcode {




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