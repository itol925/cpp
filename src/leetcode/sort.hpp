#include <iostream>
#include <vector>
#include <string>
#include <sstream>

namespace leetcode {
    std::string log(const std::vector<int>& v) {
        std::ostringstream oss;
        oss << " ";
        for (int i = 0; i < v.size();  ++i) {
            oss << v[i];
            if (i < v.size()) {
                oss << ", ";
            }
        }
        return oss.str();
    }

    namespace sort {
        /**
         * https://www.runoob.com/w3cnote/insertion-sort.html
         * @param v
         */
        void insertion_sort(std::vector<int> v) {
            std::cout << "vec:" << log(v) << std::endl;
            for (int j = 1; j < v.size(); ++j) {
                int insert = v[j];  // 待插入元素
                int i = j - 1;
                // v[j] 之前比 v[j] 大的元素依次右移，为 v[j] 腾空
                while(i >= 0 && v[i] > insert) {
                    v[i + 1] = v[i];
                    --i;
                }
                v[i + 1] = insert;
            }
            std::cout << "sort vec:" << log(v) << std::endl;
        }

        void test() {
            insertion_sort({2, 1, 3, 4, 2});
        }
    }
}