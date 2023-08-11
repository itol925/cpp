#include <iostream>

namespace stl {
    namespace ref_demo {
        template<typename T>
        void add(T t) {
            ++t;
        }

        void test() {
            int a = 1;
            int& b = a;
            add(b); // 因为模板传入的是个 value，所以 add 操作不会影响到 a 和 b
            std::cout << "b:" << b << " a:" << a << std::endl;

            add(std::ref(b));
            std::cout << "ref. b:" << b << " a:" << a << std::endl;
        }

        void add2(int&& a) {
            ++a;
        }
        void test2() {
            int a = 1;
            add2(std::move(a));
        }
    }

    namespace move_demo {
        class Cache {
        public:
            Cache(int& d) : data(d) {}
            void callData () {
                std::cout << "data:" << data << std::endl;
            }
        private:
            std::reference_wrapper<int> data;
        };

        class Ledger {
        public:
            Ledger(int&& d) :
            data(std::move(d)) {}
        private:
            int data;
        };

        void test() {
            int data = 1;
            Ledger l(std::move(data));
        }
    }
}