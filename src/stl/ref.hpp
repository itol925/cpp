#include <iostream>
#include <vector>

namespace stl {
    namespace ref_demo {
        template<typename T>
        void add(T t) {
            ++t;
        }

        void test_left_ref() {
            int a = 1;
            int &b = a;
            add(b); // 因为模板传入的是个 value，所以 add 操作不会影响到 a 和 b
            std::cout << "b:" << b << " a:" << a << std::endl;

            add(std::ref(b)); // 这里传入的 b 的引用，b 和 a 均受 add 影响
            std::cout << "ref. b:" << b << " a:" << a << std::endl;
        }

        void add2(int &&a) {
            ++a;
        }

        void test_right_ref() {
            int a2 = 1;
            add2(std::move(a2)); // 右值传递，受 add2 影响
            std::cout << "a2:" << a2 << std::endl;
        }

        // 有一些场景，比如标准容器（如std::vector）不能存储引用，因此不能改通 v[0] = xxx 的方式来修改容器里的元素值
        // 这种场景可以用 reference_wrapper
        void test_reference_wrapper() {
            int a = 1, b = 2;
            std::vector<int> v = {a, b};
            v[0] = 10; // 这里只改了 v[0]，并没有改 a 的值，因为 v 存的是 a 的拷贝
            std::cout << "v[0]=" << v[0] << ", a=" << a << std::endl;

            std::vector<std::reference_wrapper<int>> v2 = {a, b};
            v2[0].get() = 10;   // 这里改了 v[0]，同时也修改了 a，因为 v 存的是 a 的引用
            std::cout << "v2[0]=" << v2[0].get() << ", a=" << a << std::endl;
        }

        // 引用坍缩
        // 注：除了 右值引用右值（right_ref&&）坍缩成右值引用外，其他都是坍缩成左值引用
        void test_ref_collapsing() {
            typedef int &left_ref;
            typedef int &&right_ref;
            int n = 1;
            left_ref &r1 = n;   // r1 是 int&
            left_ref &&r2 = n; // r2 的类型是 int&
            right_ref &r3 = n; // r3 的类型是 int&
            right_ref &&r4 = 1; // r4 的类型是 int&&
        }

        // 左值表达式。当函数的返回值是左值引用时，函数调用表达式成为
        char &char_number(std::string &s, std::size_t n) {
            return s.at(n); // string::at() 返回 char 的引用
        }

        void test_left_expression() {
            std::string s = "abc";
            char_number(s, 0) = 'b';
            std::cout << "s=" << s << std::endl; // s="bbc" 了
        }

        // forward 完美转发
        void foo(int &a) {
            ++a;
            std::cout << "left value" << std::endl;
        }

        void foo(int &&a) {
            ++a;
            std::cout << "right value" << std::endl;
        }

        void foo(const int &a) {
            std::cout << "const left value" << std::endl;
        }

        template<typename T>
        void do_forward(T &&arg) {
            foo(std::forward<T>(arg));
        }

        void test_forward() {
            int n = 1;
            int &n2 = n;
            const int n3 = 1;
            do_forward(n);
            std::cout << "n=" << n << std::endl;
            do_forward(n2);
            std::cout << "n2=" << n2 << std::endl;
            do_forward(std::move(n));
            std::cout << "n=" << n << std::endl;
            do_forward(n3);
        }

        namespace {
            class Base {
            public:
                virtual void virtualFunc() {
                    std::cout << "base virtual func" << std::endl;
                }

                void func() {
                    std::cout << "base func" << std::endl;
                }
            };
            class Derived : public Base {
            public:
                void virtualFunc() override {
                    std::cout << "derived virtual" << std::endl;
                }

                void func() {
                    std::cout << "derived func" << std::endl;
                }
            };
        }

        void test() {
            //test_left_ref();
            //test_right_ref();
            //test_reference_wrapper();
            //test_left_expression();
            //test_forward();

            Derived derived;
            Base &base = derived;
            base.virtualFunc(); // 注：这里调用的是 derived.virtualFunc
            base.func();        // 注：这里调用的是 base.func()
        }
    }
}