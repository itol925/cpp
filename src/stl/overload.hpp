#include <iostream>
#include <cstdio>
#include <cstdlib>

namespace stl {
    // 以下运算符可以重载
    // + - * / % ^ & | ~ ! = < > += -= *= /= %= ^= &= |= << >> >>= <<= == != <= >= <=> (C++20 起) && || ++ -- , ->* -> () []

    namespace overload_demo {
        namespace {
            // 用户自定义转换函数
            struct X {
                explicit operator int() { return 7; }

                explicit operator int *() { return nullptr; }
            };

            void test_user_define_conversion() {
                X x;
                int n = static_cast<int>(x);
                std::cout << "user define conversion. n:" << n << std::endl;
            }
        }

        namespace {
            // 重载 new delete。注：new delete 重载函数必须全局的
            //void* operator new(std::size_t sz) {
            //    std::printf("global op new called, size = %zu\n",sz);
            //    void *ptr = std::malloc(sz);
            //    if (ptr)
            //        return ptr;
            //    else
            //        throw std::bad_alloc{};
            //}
            //void operator delete(void* ptr) noexcept {
            //    std::puts("global op delete called");
            //    std::free(ptr);
            //}
            //void test_allocation() {
            //    int* p1 = new int;
            //    delete p1;
            //
            //    int* p2 = new int[10]; // C++11 中保证调用替换者
            //    delete[] p2;
            //}
        }

        namespace {
            // 重载数组符。
            // 提供数组式访问并同时允许读写的用户定义类，典型地为 operator[] 定义两个重载：const 和非 const 变体
            struct T {
                std::vector<int> myVector;

                int &operator[](std::size_t idx) { return myVector[idx]; }

                const int &operator[](std::size_t idx) const { return myVector[idx]; }
            };
        }

        void test() {
            overload_demo::test_user_define_conversion();
        }
    }
}