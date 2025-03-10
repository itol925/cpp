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
        // 注：下面的实现不需要有序数组
        vector<int> twoSum(vector<int>& nums, int target) {
            std::unordered_map<int, int> numMap;
            for (int i = 0; i < nums.size(); i++) {
                int other = target - nums[i];
                if (numMap.find(other) != numMap.end()) {
                    return {i, numMap[other]};
                }
                numMap.insert({nums[i], i});
            }
            return {};
        }

        void test() {
            vector<int> arr = {3,2,4};
            int target = 6;
            cout << "two sum = " << target << ":" << array_to_string(twoSum(arr, target)) << endl;
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
    namespace linked_list_cycle {
        /**
         * 快慢指针
         * 给定一个链表，如果有环路，找出环路的开始点
         * 思路：给定两个指针，从起点开始，fast指针走2步，slow指针走1步，
         * 如果快指针能走到尽头，说明没有环路，否则一定有环路，且必定会与slow相遇。
         * 如何找环路起点？
         * 在fast与slow第一次相遇的时候，我们将fast重新移动到链表的开头，并且和slow一起，每次走1步，
         * 当slow和fast第二次相遇的时候，相遇的节点即为环路的开始点
         */
         struct Node {
             int value;
             Node* next;
             Node(int v, Node* n) : value(0), next(nullptr) {
                 value = v;
                 next = n;
             }
         };
         Node* detectCycle(Node* head) {
             Node* fast = head, *slow = head;
             while(fast->next && fast->next->next) {
                 fast = fast->next->next;
                 slow = slow->next;
                 if (fast == slow) {
                     break;
                 }
             }
             if (fast != slow) {
                 return nullptr;
             }
             fast = head;
             while(fast != slow) {
                 fast = fast->next;
                 slow = slow->next;
             }
             return fast;
         }
         void test() {
             Node* node0 = new Node(0, nullptr);
             Node* node1 = new Node(1, nullptr);
             Node* node2 = new Node(2, nullptr);
             Node* node3 = new Node(3, nullptr);

             node0->next = node1;
             node1->next = node2;
             node2->next = node3;
             node3->next = node1;

             Node* cycleNode = detectCycle(node0);
             if (cycleNode) {
                 cout << "linked_list_cycle. cycleNode:" << cycleNode->value << endl;
             } else {
                 cout << "linked_list_cycle. cycleNode: null" << endl;
             }

             delete node0;
             delete node1;
             delete node2;
             delete node3;
         }
    }

    namespace minimum_window_substring {
        /**
         * 滑动窗口
         * 给定两个字符串 S 和 T，求 S 中包含 T 所有字符的最智囊连续子字符串的长度，同时要求时间复杂度不超过O(n).
         * 比如 input:S = "ADOBECODEBANC"，T = "ABC"，output:"BANC"
         */
        string do_mws(string s, string t) {
            int has[128] = { 0 };
            size_t fill = t.size(), start = s.size(), end = s.size(), min = std::numeric_limits<size_t>::max();
            for (size_t i = fill; i--; ) {
                ++has[t[i]];
            }
            for (size_t i = s.size(); i--; ) {
                if (has[s[i]]-- > 0) {
                    if (fill == 1) {
                        while (has[s[--end]]++ != 0) {}
                        size_t len = end - i + 1U;
                        if (len < min) {
                            min = len;
                            start = i;
                        }
                    } else {
                        --fill;
                    }
                }
            }
            return s.substr(start, min);
        }
        string do_mws1(string s, string t) {
            int flags[128] = { 0 }; // 存储t中各字符的数量，用于match后重置nums
            for (int i = 0; i < t.size(); ++i) {
                ++flags[t[i]];
            }
            int cnt = 0, r = 0, min = s.size() + 1;
            int nums[128] = {0};    // 存储t中各字符的数量，用于过程统计
            std::memcpy(nums, flags, sizeof(flags));
            string res;
            for (int l = 0; l < s.size(); ++l) {
                if (nums[s[l]]-- > 0) { // 右移l指针，直到遇到t字符串的字符，再开始右移r指针
                    cnt++;
                    for (r = l + 1; r < s.size(); ++r) { // 右移r指针，直到全部match t字符串
                        if (nums[s[r]]-- > 0) {
                            cnt++;
                            if (cnt == t.size()) { // 完全match。重置t中各字符串的数量
                                cout << "match:" << s.substr(l, r - l + 1) << endl;
                                // 重置 nums
                                std::memcpy(nums, flags, sizeof(flags));
                                cnt = 0;
                                if (r - l + 1 < min) {
                                    min = r - l + 1;
                                    res = s.substr(l, r - l + 1);
                                }
                                break;
                            }
                        }
                    }
                }
            }
            return res;
        }
        void test() {
            string S = "ADOBECODEBANC", T = "ABC";
            cout << "minimum_window_substring. S=" << S << ", T=" << T << endl;
            string str = do_mws1(S, T);
            cout << "ans:" << str << endl;
        }
    }
}