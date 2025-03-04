#include <vector>
#include <iostream>
#include "common/common.hpp"

using namespace std;
using common::array_to_string;

namespace leetcode {

    void test() {
        vector<int> nums = {1,null,3,4,5};
        TreeNode* root = newTree(nums);
        cout << (tree_to_string(root)) << endl;
        freeTree(root);
    }

}