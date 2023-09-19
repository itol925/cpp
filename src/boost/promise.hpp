#include <continuable/continuable.hpp>
#include <iostream>
#include <thread>

namespace promise_demo {
    cti::continuable<int> async(int arg) {
        std::cout << "async" << std::endl;
        return cti::make_continuable<int>([arg](cti::promise<int> p){
            std::cout << "async start" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

            if (arg % 3 == 0) {
                p.set_value(arg + 1);
                std::cout << "async success" << std::endl;
            } else if (arg % 3 == 1) {
                std::exception_ptr ptr;
                p.set_exception(ptr);
                std::cout << "async exception" << std::endl;
            } else if (arg % 3 == 2) {
                p.set_canceled();
                std::cout << "async canceled" << std::endl;
            }
        });
    }

    void test() {
        async(3).then([](int result) {
            std::cout << "result:" << result << std::endl;
        }).fail([](){
            std::cout << "failed" << std::endl;
        });
    }
}