#include <iostream>
#include <type_traits>
#include <string>
#include <chrono>
#include <thread>

#pragma once

namespace common {
    using namespace std;
    void sleep(int milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds (milliseconds));
    }

    /**
    * 产生[a,b)的随机数，可以使用
    * @param a
    * @param b
    * @return
    */
    int random(int a, int b) {
        return (rand() % (b - a)) + a;
    }

    /**
     * [0, 100) 之间的随机数
     * @return
     */
    int random() {
        return random(0, 100);
    }

    /*
     * 打印数组
     */
    // 基础模板（默认情况）
    template<typename T>
    struct is_vector : std::false_type {};

    // 特化模板（对于 std::vector<T, Allocator>）
    template<typename T, typename Allocator>
    struct is_vector<std::vector<T, Allocator>> : std::true_type {};

    template<typename T>
    std::string array_to_string(const std::vector<T> &arr) {
        std::ostringstream oss;
        oss << "[";
        for (int i = 0; i < arr.size(); i++) {
            if constexpr (is_vector<T>::value) {
                oss << array_to_string(arr[i]);
            } else {
                oss << arr[i];
            }
            if (i != arr.size() - 1) oss << ", ";
        }
        oss << "]";
        return oss.str();
    }

    int null = INFINITY;
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };
    namespace {
        TreeNode* constructTree(vector<int>& nums, int left, int right) {
            if (left > right) return nullptr;  // 递归终止条件

            int mid = left + (right - left) / 2;  // 选择中点
            TreeNode* root = new TreeNode(nums[mid]);  // 创建根节点

            root->left = constructTree(nums, left, mid - 1);  // 递归构造左子树
            root->right = constructTree(nums, mid + 1, right);  // 递归构造右子树

            return root;
        }
    }

    TreeNode* newTree(vector<int>& nums) {
        return constructTree(nums, 0, (int)nums.size() - 1);
    }
    void freeTree(TreeNode* root) {
        if (!root) {
            return;
        }
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }

    /**
     * 中序遍历（左->根->右顺序，即根在中。前序为根->左->右，后序为左->右->根）
     * @param root
     * @return
     */
    string tree_to_string(TreeNode* root) {
        if (!root) return "";
        std::ostringstream oss;
        oss << tree_to_string(root->left);
        if (root->val == null) {
            oss << "null" << " ";
        } else {
            oss << root->val << " ";
        }
        oss << tree_to_string(root->right);
        return oss.str();
    }
}