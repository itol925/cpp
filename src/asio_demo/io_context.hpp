#include <asio.hpp>
#include <iostream>
#include <thread>
#include <chrono>

namespace asio_demo::io_context {
    // ref:https://zhuanlan.zhihu.com/p/583533338
    // ref:https://blog.csdn.net/hezhanran/article/details/110665606
    // ref:https://zhuanlan.zhihu.com/p/179070263
    // ref:https://mmoaay.gitbooks.io/boost-asio-cpp-network-programming-chinese/content/Chapter2.html

    /* io_context 成员函数
     * run：阻塞式运行 io_context 对象的事件处理循环，直到所有异步操作都完成或 stop 函数被调用。
     * stop：停止 io_context 对象的事件处理循环。
     * stopped：判断 io_context 对象是否已停止。
     * restart：重启 io_context 对象，以便再次运行事件处理循环。
     * poll：非阻塞式运行 io_context 对象的事件处理循环，以执行所有就绪的处理程序。
     * poll_one：运行 io_context 对象的事件处理循环，以执行一个就绪的处理程序。
     * get_executor：获取与 io_context 对象关联的执行器
     * run_for：运行 io_context 对象的事件处理循环，直到所有异步操作都完成、stop 函数被调用或指定的持续时间已过。
     * run_one：运行 io_context 对象的事件处理循环，以执行最多一个处理程序。
     * run_one_for：运行 io_context 对象的事件处理循环，直到执行了最多一个处理程序、stop 函数被调用或指定的持续时间已过。
     * run_one_until：运行 io_context 对象的事件处理循环，直到执行了最多一个处理程序、stop 函数被调用或指定的时间已过。
     * run_until：运行 io_context 对象的事件处理循环，直到所有异步操作都完成、stop 函数被调用或指定的时间已过。
     * */
    void handler() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "task1 done" << std::endl;
    }

    void test_post() {
        asio::io_context io_context;
        io_context.post(handler);

        io_context.post([] {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "task2 done" << std::endl;
        });
        std::cout << "test io context.." << std::endl;
        // 注：io_context 会依次串行调用 task1, task2，执行完后，run 返回
        io_context.run();
        std::cout << "test io context done" << std::endl;
    }

    void test_post_work_guard() {
        asio::io_context io_context;
        io_context.post([] {
            std::cout << "task1 done" << std::endl;
        });
        io_context.post([] {
            std::cout << "task2 done" << std::endl;
        });
        // work_guard 给 io_context 任务数加 1，所以只要 work_guard 不 reset，io_context.run 是不会返回的。相当于 hold 住了 io_context
        auto work_guard = asio::make_work_guard(io_context);

        std::thread t([&io_context] {
            std::cout << "io_context run.." << std::endl;
            io_context.run();
            std::cout << "io_context run done" << std::endl;
        });

        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "work reset" << std::endl;
        work_guard.reset(); // 允许 io_context.run 返回
        t.join();
    }

    void test_poll() {
        asio::io_context io_context;
        io_context.post([] {
            std::cout << "task done" << std::endl;
        });
        io_context.post([] {
            std::cout << "task2 done" << std::endl;
        });
        asio::io_context::work work(io_context); // work 析构时，允许 io_context.run 返回
        std::cout << "poll 1" << std::endl;
        io_context.poll(); // 立即执行 io_context 的事件队列，非阻塞式的
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "poll 2" << std::endl;
        io_context.poll();
    }

    void test_poll_by_multi_thread() {
        // io_context 被多个线程执行 run 的情况
        asio::io_context io;

        io.post([] {
            std::cout << "Hello from thread " << std::this_thread::get_id() << "\n";
        });
        io.post([] {
            std::cout << "Hello from thread " << std::this_thread::get_id() << "\n";
        });

        std::thread t1([&io] {
            io.run();
            std::cout << "io done " << std::this_thread::get_id() << "\n";
        });
        std::thread t2([&io] {
            io.run();
            std::cout << "io done " << std::this_thread::get_id() << "\n";
        });

        t1.join();
        t2.join();
    }
}