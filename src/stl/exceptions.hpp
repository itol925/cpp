#include <algorithm>
#include <cstring>
#include <exception>
#include <iostream>
#include <mutex>
#include <string>

namespace stl {
    namespace exception_demo {
        void divide_zero() {
            try {
                int i = 0;
                int x = 19 / i;
            } catch (std::exception &e) {
                std::cout << "divide zero:" << e.what() << std::endl;
            }
        }

        void safe_func() noexcept {
            // 不抛异常的函数
        }

        void no_throw() {
            std::string domain = "www.baidu.com";
            try {
                // 注：数组越界，但[ ] 没有抛出异常的能力，所以不可能会catch到东西
                char c1 = domain[100];
                std::cout << c1 << std::endl;
            } catch (std::exception e) {
                std::cout << "will not execute" << e.what() << std::endl;
            }
        }

        void throw_by_string() {
            std::exception_ptr eptr;
            std::string domain = "www.baidu.com";
            try {
                // 数组越界，抛出异常
                char c1 = domain.at(100);
                std::cout << c1 << std::endl;
            } catch (std::exception e) {
                std::cout << "throw by std::string:" << e.what() << std::endl;

                eptr = std::current_exception();
            }

            if (eptr != nullptr) {
                std::rethrow_exception(eptr);
            }
        }

        void throw_manual() {
            std::string domain = "www.baidu.com";
            try {
                throw "this is an exception";
            } catch (const char *e) {
                std::cout << "throw string:" << e << std::endl;
            }

            int i = 0;
            try {
                throw i;
            } catch (const int &e) {
                std::cout << "throw int:" << e << std::endl;
            }
        }
    }

    void test() {
        std::cout << "---- base exception" << std::endl;
        exception_demo::divide_zero();
        exception_demo::no_throw();
        try {
            exception_demo::throw_by_string();
        } catch (std::exception &e) {
            std::cout << "rethrow" << e.what() << std::endl;
        }
        exception_demo::throw_manual();
    }
}
