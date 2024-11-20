#include <continuable/continuable.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include "common/common.hpp"


namespace continue_demo {
    namespace install {
        // git clone https://github.com/Naios/continuable.git
        // git submodule init
        // git submodule update

        //cd continuable
        //mkdir build
        //cd build
        //cmake ..

        //make
        //sudo make install
    }

    namespace thread_demo {
        using namespace boost;

        void test_post() {
            asio::io_context io_context;
            asio::post(io_context, cti::use_continuable).then([] {
                std::this_thread::sleep_for(std::chrono::seconds(5));
            });
            std::thread t([&io_context] {
                std::cout << "context start.. " << std::endl;
                io_context.run();
                std::cout << "context start end" << std::endl;
            });
            t.join();
        }

        /**
         * work guard 用法.
         * context 添加 guard 后，将保持 context 的活动状态（io_context.run函数不返回），直到 work_guard 调用 reset 函数
         */
        void test_guard() {
            asio::io_context io_context;
            auto work = asio::make_work_guard(io_context);
            asio::post(io_context, cti::use_continuable).then([] {
                std::this_thread::sleep_for(std::chrono::seconds(5));
            });
            std::thread t([&io_context] {
                std::cout << "block on io_context.run().." << std::endl;
                io_context.run();
                std::cout << "永远不会执行到这里" << std::endl;
            });
            // work.reset();
            t.join();
        }

        /**
         * 单线程，多 task 情况
         * 所有的 post 任务分配给一个线程，依次串行执行
         */
        void test_multi_task() {
            asio::io_context io_context;
            for (int i = 0; i < 10; i++) { // 添加 10 个任务
                asio::post(io_context, [i] {
                    std::cout << std::this_thread::get_id() << ".task." << i << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                });
            }
            std::thread t([&io_context] {
                io_context.run();
            });
            t.join();
        }

        /**
         * post then 用法
         * 所有的 then 用一个线程
         */
        void test_multi_then() {
            asio::io_context io_context;
            asio::post(io_context, cti::use_continuable).then([] {
                std::cout << std::this_thread::get_id() << ".task1" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }).then([] {
                std::cout << std::this_thread::get_id() << ".task2" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }).then([] {
                std::cout << std::this_thread::get_id() << ".task3" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }).then([] {
                std::cout << std::this_thread::get_id() << ".task4" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }).then([] {
                std::cout << std::this_thread::get_id() << ".task5" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            });
            std::thread t([&io_context] {
                io_context.run();
            });
            t.join();
        }

        /**
         * 多 then 多 thread
         * 所有的 then 还是由同一个线程执行
         */
        void test_multi_then_multi_thread() {
            asio::io_context io_context;
            asio::post(io_context, cti::use_continuable).then([] {
                std::cout << std::this_thread::get_id() << ".task1" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }).then([] {
                std::cout << std::this_thread::get_id() << ".task2" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }).then([] {
                std::cout << std::this_thread::get_id() << ".task3" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }).then([] {
                std::cout << std::this_thread::get_id() << ".task4" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }).then([] {
                std::cout << std::this_thread::get_id() << ".task5" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            });

            asio::thread_pool thread_pool(5);
            for (int i = 0; i < 5; ++i) {
                asio::post(thread_pool, [&io_context, &thread_pool]() {
                    try {
                        io_context.run();
                    } catch (const std::exception &e) {
                        thread_pool.stop();
                    }
                });
            }
            thread_pool.join();
        }

        /**
         * 多 thread 多 task
         * 各个任务分配到不同的线程执行
         */
        void test_multi_thread_multi_task() {
            asio::io_context io_context;
            for (int i = 0; i < 10; i++) {
                asio::post(io_context, [i] {
                    std::this_thread::sleep_for(std::chrono::milliseconds(common::random(100, 1000)));
                    std::cout << std::this_thread::get_id() << ".task." << i << std::endl;
                });
            }
            asio::thread_pool thread_pool(5);
            for (int i = 0; i < 5; ++i) {
                asio::post(thread_pool, [&io_context, &thread_pool]() {
                    try {
                        io_context.run();
                    } catch (const std::exception &e) {
                        thread_pool.stop();
                    }
                });
            }
            thread_pool.join();
        }

        /**
         * multi task multi task with guard
         * 先运行 context ，再给 context 添加任务
         */
        void test_multi_thread_multi_task2() {
            asio::io_context io_context;
            auto work = asio::make_work_guard(io_context);
            asio::thread_pool thread_pool(5);
            for (int i = 0; i < 5; ++i) {
                asio::post(thread_pool, [&io_context, &thread_pool]() {
                    try {
                        io_context.run();
                    } catch (const std::exception &e) {
                        thread_pool.stop();
                    }
                });
            }

            int i = 100;
            while (--i >= 0) {
                asio::post(io_context, [i] {
                    std::this_thread::sleep_for(std::chrono::milliseconds(common::random(100, 1000)));
                    std::cout << std::this_thread::get_id() << ".task." << i << std::endl;
                });
            }
        }

        void test3() {
            asio::io_context io_context;
            int *p = nullptr;
            std::cout << "p:" << p << std::endl;
            asio::post(io_context, cti::use_continuable).then([p] {
                // p = new int(1); error! 不能给 copy 变量赋值
                std::cout << "p2:" << p << std::endl;
            });
            std::thread t([&io_context] {
                io_context.run();
            });
            t.join();
        }
    }

    void test() {
        srand((unsigned) time(nullptr));
        thread_demo::test_multi_thread_multi_task2();
    }
}



