#include <continuable/continuable.hpp>
#include <asio.hpp>
#include <iostream>
#include "common/common.hpp"

namespace continuable_demo {
    namespace install {
        // git clone https://github.com/Naios/continuable.git
        // https://naios.github.io/continuable/tutorial.html
    }

    void test() {
        cti::make_ready_continuable().then([] {
            std::cout << "hello " << std::endl;
        }).then([] {
            common::sleep(2000);
            std::cout << "world!" << std::endl;
        });
    }

    void test_exception() {
        cti::make_ready_continuable().then([]{
            std::cout << "ok" << std::endl;
        }).then([] {
            std::cout << "ok2" << std::endl;
        }).then([] {
            throw std::runtime_error("An error occurred!");
        }).then([] {
            std::cout << "ok4" << std::endl;
        }).fail([](const std::exception_ptr& ptr) {
            try {
                std::rethrow_exception(ptr);
            } catch(std::exception const& e) {
                std::cerr << "Caught exception: " << e.what() << std::endl;
            }
        });
    }

    auto sth_err() {
        return cti::make_continuable<void>([=] (auto&& promise) {
            try {
                // Usually the exception is thrown by another expression
                throw std::exception {};
            } catch(...) {
                promise.set_exception(std::current_exception());
            }
        });
    }
    void test_exception2() {
        sth_err().then([] {
            std::cout << "ok" << std::endl;
        }).fail([](const std::exception_ptr& ptr) {
            try {
                std::rethrow_exception(ptr);
            } catch(std::exception const& e) {
                std::cerr << "Caught exception: " << e.what() << std::endl;
            }
        });
    }

    static void do_sth() {
        common::sleep(1000);
        std::cout << "do sth" << std::endl;
    }
    void test_with_executor() {
        auto executor = [](auto&& work) {
            // Dispatch the work here, store it for later
            // invocation or move it to another thread.
            std::forward<decltype(work)>(work)();
        };
        cti::make_ready_continuable().then([]{
            do_sth();
        }, executor);
    }

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
}



