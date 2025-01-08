#include <iostream>
#include <vector>
#include <stack>
#include <numeric>

using namespace std;
namespace leetcode::binary_search {
    namespace binary_search {
        // 二分查找，针对有序数组
        int binary_search(vector<int> arr, int target) {
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
        void test() {
            std::vector<int> arr = {1, 2, 3, 4, 5, 6};
            int target = 3;
            int index = binary_search(arr, target);
            cout << "binary_search index:" << index << endl;
        }
    }

    namespace my_sqrt {
        /*
         * 给一个非负数，求其开方，向下取整
         */
        int my_sqrt(int n) {
            if (n == 0)
                return n;
            int l = 1, r = n, mid, sqrt;
            while (l <= r) {
                mid = l + (r - l)/2;
                sqrt = n/mid;
                if (mid == sqrt) {
                    return sqrt;
                } else if (mid > sqrt) { // 说明结果在 l~mid 区间
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            return r;
        }
        void test() {
            int n = 7;
            cout << "my sqrt: n=" << n << " sqrt:" << my_sqrt(n) << endl;
        }
    }
}