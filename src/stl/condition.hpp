#include <iostream>
#include <thread>
#include "common/common.hpp"

namespace condition_demo {
    void test() {
        std::thread t([]{
            std::cout << "sleep..\n";
            common::WaitUtil::sleep(2000);
            std::cout << "notify..\n";
            common::WaitUtil::notify();
        });
        std::cout << "wait..\n";
        common::WaitUtil::wait();
        std::cout << "done..\n";

        t.join();
    }
}