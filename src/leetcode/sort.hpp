#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "common/common.hpp"

namespace leetcode::sort {
    /**
     * 插入排序
     * https://www.runoob.com/w3cnote/insertion-sort.html
     *
     */
    void insertion_sort(std::vector<int> v) {
        std::cout << "vec:" << common::array_to_string(v) << std::endl;
        for (int j = 1; j < v.size(); ++j) {
            int insert = v[j];  // 待插入元素
            int i = j - 1;
            // v[j] 之前比 v[j] 大的元素依次右移，为 v[j] 腾空
            while (i >= 0 && v[i] > insert) {
                v[i + 1] = v[i];
                --i;
            }
            v[i + 1] = insert;
        }
        std::cout << "sort vec:" << common::array_to_string(v) << std::endl;
    }

    /**
     * 归并排序
     * https://www.runoob.com/w3cnote/merge-sort.html
     */
    void merge(std::vector<int> &arr, int front, int mid, int end) {
        std::vector<int> left(arr.begin() + front, arr.begin() + mid + 1);
        std::vector<int> right(arr.begin() + mid + 1, arr.begin() + end + 1);
        left.insert(left.end(), std::numeric_limits<int>::max());
        right.insert(right.end(), std::numeric_limits<int>::max());

        int leftIndex = 0, rightIndex = 0;
        for (int i = front; i <= end; ++i) {
            if (left[leftIndex] < right[rightIndex]) {
                arr[i] = left[leftIndex];
                ++leftIndex;
            } else {
                arr[i] = right[rightIndex];
                ++rightIndex;
            }
        }
    }

    void merge_sort(std::vector<int> &arr, int front, int end) {
        if (front >= end) {
            return;
        }
        int mid = (front + end) / 2;
        merge_sort(arr, front, mid);
        merge_sort(arr, mid + 1, end);
        merge(arr, front, mid, end);
    }

    void merge_sort(std::vector<int> arr) {
        std::cout << "vec:" << common::array_to_string(arr) << std::endl;
        merge_sort(arr, 0, arr.size() - 1);
        std::cout << "sort vec:" << common::array_to_string(arr) << std::endl;
    }

    /**
    * 最大子数组
    * 暴力解析
    */
    void max_sub_arr() {
        std::vector<int> arr = {1, 3, -2, 4, 5, 6, -7, 3, 2, 11};
        int max_sum = INT32_MIN;
        int sum = 0;
        for (int i = 0; i < arr.size(); ++i) {
            sum = arr[i];
            for (int j = i + 1; j < arr.size(); j++) {
                if (arr[j] < 0) {
                    break;
                }
                sum += arr[j];
                if (sum > max_sum) {
                    max_sum = sum;
                }
            }
        }
        std::cout << "max_sum:" << max_sum << std::endl;
    }

    /**
    * 快速排序
    */
    void quick_sort(std::vector<int>& arr, int l, int r) {
        if (l + 1 >= r) {
            return;
        }
        int first = l, last = r - 1, key = arr[first];
        while(first < last) {
            while(first < last && arr[last] >= key) { // 从后往前找到比 key 大的元素，替换 first
                --last;
            }
            arr[first] = arr[last];
            while(first < last && arr[first] <= key) { // 从前往后找到比 key 小的元素，替换 last
                ++first;
            }
            arr[last] = arr[first];
        }
        arr[first] = key;
        quick_sort(arr, l, first);
        quick_sort(arr, first + 1, r);
    }

    /** 桶排序
     * 指定一个数组，求前K个最频繁的数字 Medium
     * 如 nums = [1,1,1,1,2,2,3,4]，k=2，则输出 [1,2]
     * step1: 设立一个桶 counts，将各值出现的次数
     * step2：对桶按 value 进行排序
     */
    void topKFrequentElement() {
        std::vector<int> nums = {0,1, 1, 1, 1, 2, 2, 3, 4};
        int k = 2;

        std::unordered_map<int, int> counts;
        int max_count = 0;
        for (const int& num : nums) {
            max_count = std::max(max_count, ++counts[num]);
        }

        std::vector<std::vector<int>> buckets;
        for (const auto& p : counts) {
            buckets.push_back({p.first, p.second});
        }

        for (int i = 0; i < buckets.size(); ++i) {
            for (int j = i + 1; j < buckets.size(); ++j) {
                if (buckets[i][1] < buckets[j][1]) {
                    std::swap(buckets[i], buckets[j]);
                }
            }
        }

        for (int i = 0; i < k; ++i) {
            std::cout << buckets[i][0] << ",";
        }
    }

    void test() {
        //std::vector<int> arr = {2, 1, 3, 5, 7, 6};
        //insertion_sort(arr);
        //merge_sort(arr);
        //max_sub_arr();
        //quick_sort(arr, 0, 5);
        //std::cout << log(arr);
        topKFrequentElement();
    }
}