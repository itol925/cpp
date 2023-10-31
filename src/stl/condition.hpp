#include <iostream>
#include <thread>
#include "common/common.hpp"

namespace condition_demo {
    namespace {
        std::mutex mutex_;
        std::condition_variable cv_;
        bool condition_ = false;

        /**
         * block current thread
         */
        void wait() {
            std::unique_lock<std::mutex> lock(mutex_);
            condition_ = false;
            cv_.wait(lock, [] { return condition_; });
        }

        /**
         * continue this thread
         */
        void notify() {
            std::lock_guard<std::mutex> lock(mutex_);
            condition_ = true;
            cv_.notify_one();
        }
    }

    void test() {
        std::thread t([]{
            std::cout << "sleep..\n";
            common::sleep(2000);
            std::cout << "notify..\n";
            notify();
        });
        std::cout << "wait..\n";
        wait();
        std::cout << "done..\n";

        t.join();
    }
}