#include <iostream>
#include <functional>

namespace stl {
    namespace func {
        // 函数可通过返回或者抛出异常终止

        namespace func_ptr { // 函数指针
            int add(int a, int b) {
                return a + b;
            }

            // 定义函数指针
            typedef int (*add_ptr)(int, int);

            void test() {
                add_ptr p_add = &add;
                std::cout << p_add(1, 1) << std::endl;

                add_ptr p_add2 = add; // &可省
                std::cout << p_add2(1, 1) << std::endl;

                int (*p_add3)(int, int) = add;
                std::cout << p_add3(1, 1) << std::endl;
            }
        }

        namespace lambda_demo { // lambda. since c++11
            auto my_add = [](int a, int b) {
                return a + b;
            };

            void test() {
                std::cout << "sort:" << my_add(2, 1) << std::endl;
            }
        }

        namespace function_demo {
            void print_num(int i) {
                std::cout << "num:" << i << std::endl;
            }

            void print_num2(int i, int k, const int &j) {
                std::cout << "num2:" << i << "," << k << "," << j << std::endl;
            }

            struct Obj {
            public:
                void print(int i) {
                    std::cout << "num:" << i << std::endl;
                }
            };

            void test() {
                std::function<void(int)> f = print_num;
                f(10);

                std::function<void(int)> f2 = [](int i) {
                    print_num(i);
                };
                f2(11);

                std::function<void()> f3 = std::bind(print_num, 12);
                f3();

                std::function<void(int)> f4 = std::bind(print_num, std::placeholders::_1);
                f4(13);

                Obj obj;
                std::function<void(int)> f5 = std::bind(&Obj::print, obj, std::placeholders::_1);
                f5(14);

                using namespace std::placeholders;
                int n = 17;
                std::function<void(int, int, const int &)> f6 = std::bind(print_num2, 15, _2, std::cref(n));
                f6(0, 16, n);
            }
        }

        namespace function_template {
            template<typename F, typename... Args>
            void my_post(F &&f, Args &&... args) {
                std::function<void(Args...)> func(std::forward<F>(f));
                func(std::forward<Args>(args)...);
            }

            void my_function(int a, int b) {
                std::cout << a + b << std::endl;
            }

            void my_function2(int a, int b, int c) {
                std::cout << a + b + c << std::endl;
            }

            void test() {
                my_post(my_function, 3, 4);
                my_post(my_function2, 3, 4, 5);
                my_post([]() {
                    std::cout << "ok" << std::endl;
                });
            }
        }

        void test() {
            //function_demo::test();
            function_template::test();
        }
    }
}