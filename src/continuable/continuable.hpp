#include <continuable/continuable.hpp>
#include <continuable/external/asio.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <thread>

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
        void test() {
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

        void test2() {
            // 一个 context 接收任务派发给多个 thread 执行的情况。
            // 一个 post 任务只会派给一个线程，不会重复执行。
            // continuable 任务多个 then() 串联时，所有 then 回调由一个线程处理
            asio::io_context io_context;
            auto work = asio::make_work_guard(io_context);
            for (int i = 0; i < 10; i++) { // 添加 10 串行个任务
                asio::post(io_context, [i]{
                    std::cout << std::this_thread::get_id() << ".task0." << i << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                });
            }

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
            for (int i = 0; i < 3; ++i) {
                asio::post(thread_pool, [&io_context, &thread_pool]() {
                    try {
                        io_context.run();
                    } catch (const std::exception &e) {
                        thread_pool.stop();
                    }
                });
            }
            for (int i = 0; i < 20; i++) { // 添加 10 串行个任务
                asio::post(io_context, [i]{
                    std::cout << std::this_thread::get_id() << ".task1." << i << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                });
            }
            work.reset();
            thread_pool.join();
        }

        cti::continuable<> void_func() {
            std::cout << "void_func" << std::endl;
            return cti::make_ready_continuable();
        }
        cti::continuable<int> int_func() {
            std::cout << "int_func" << std::endl;
            return cti::make_ready_continuable(1);
        }
        void test3() {
            asio::io_context io_context;
            asio::post(io_context, cti::use_continuable).then([] {
                return void_func().then([](){
                    return int_func();
                });
            });
            std::thread t([&io_context] {
                io_context.run();
            });
            t.join();
        }

        void test4() {
            asio::io_context io_context;
            int* p = nullptr;
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
        thread_demo::test3();
    }
}


