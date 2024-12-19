#include <iostream>
#include "common/common.hpp"

namespace stl::ptr {
    class A {
    public:
        void test1(int a) {
            std::cout << "call test:" << a << std::endl;
        }
    };

    void test() {
        // 获取对象成员函数的指针
        void (A::*test)(int) = &A::test1;

        A a;
        A* pa = &a;
        (pa->*test)(100);   // 注：这里需要使用 a 的指针来用
        //a.*test(100);     // 像这样是编译不过的

        auto test2 = &A::test1; // 也可以用 auto
        (pa->*test2)(200);
    }
}