#include <iostream>

#pragma once

namespace common {
    namespace WaitUtil{
        std::mutex mutex_;
        std::condition_variable cv_;
        bool condition_ = false;

        /**
         * block current thread
         */
        void wait() {
            std::unique_lock<std::mutex> lock(mutex_);
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

        void sleep(int milliseconds) {
            std::this_thread::sleep_for(std::chrono::milliseconds (milliseconds));
        }
    }

    /**
    * 产生[a,b)的随机数，可以使用
    * @param a
    * @param b
    * @return
    */
    int random(int a, int b) {
        return (rand() % (b - a)) + a;
    }

    /**
     * [0, 100) 之间的随机数
     * @return
     */
    int random() {
        return random(0, 100);
    }
}