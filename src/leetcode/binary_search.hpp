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
}