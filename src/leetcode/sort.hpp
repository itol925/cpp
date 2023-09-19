#include <iostream>
#include <vector>
#include <string>
#include <sstream>

namespace leetcode {
    std::string log(const std::vector<int> &v) {
        std::ostringstream oss;
        oss << " ";
        for (int i = 0; i < v.size(); ++i) {
            oss << v[i];
            if (i < v.size()) {
                oss << ", ";
            }
        }
        return oss.str();
    }

    namespace sort {
        /**
         * 插入排序
         * https://www.runoob.com/w3cnote/insertion-sort.html
         */
        void insertion_sort(std::vector<int> v) {
            std::cout << "vec:" << log(v) << std::endl;
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
            std::cout << "sort vec:" << log(v) << std::endl;
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
            std::cout << "vec:" << log(arr) << std::endl;
            merge_sort(arr, 0, arr.size() - 1);
            std::cout << "sort vec:" << log(arr) << std::endl;
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
                while(first < last && arr[last] >= key) {
                    --last;
                }
                arr[first] = arr[last]; // 找到比 key 大的元素，排在 key 的前面
                while(first < last && arr[first] <= key) {
                    ++first;
                }
                arr[last] = arr[first]; // 找到比 key 小的元素，排在 key 的后面
            }
            arr[first] = key;
            quick_sort(arr, l, first);
            quick_sort(arr, first + 1, r);
        }

        void test() {
            std::vector<int> arr = {2, 1, 3, 5, 7, 6};
            //insertion_sort(arr);
            //merge_sort(arr);
            //max_sub_arr();
            quick_sort(arr, 0, 5);
            std::cout << log(arr);
        }
    }
}