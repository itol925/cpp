#include <iostream>
#include <future>
#include <thread>
#include "common/common.hpp"

namespace stl {
    namespace promise_demo {
        void doSth(std::promise<int>&& pro) {
            common::sleep(1000);
            // pro.set_value(10086);

            try {
                throw std::runtime_error("some error");
            } catch (...) {
                pro.set_exception(std::current_exception());
            }
        }

        void test() {
            std::promise<int> promise;
            std::cout << "get_future..\n";
            std::future<int> future = promise.get_future();
            std::cout << "run thread..\n";
            std::thread th(doSth, std::move(promise));

            try {
                std::cout << "future.get()=";
                int v = future.get();
                std::cout << v << std::endl;
            } catch (const std::exception& e) {
                std::cout << "exception:" << e.what() << std::endl;
            }

            th.join();
        }
    }
}