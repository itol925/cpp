#include <iostream>

namespace stl {
    namespace func {
        // 函数可通过返回或者抛出异常终止

        namespace { // 函数指针
            using namespace std;

            int add(int a, int b) {
                return a + b;
            }

            // 定义函数指针
            typedef int (*add_ptr)(int, int);

            void test_func_ptr() {
                add_ptr p_add = &add;
                std::cout << p_add(1, 1) << std::endl;

                add_ptr p_add2 = add; // &可省
                std::cout << p_add2(1, 1) << std::endl;

                int (*p_add3)(int, int) = add;
                std::cout << p_add3(1, 1) << std::endl;
            }
        }

        namespace { // lambda. since c++11
            auto my_add = [](int a, int b) {
                return a + b;
            };

        }

        void test_func() {
            using namespace std;
            std::cout << "sort:" << my_add(2, 1) << std::endl;
        }
    }
}