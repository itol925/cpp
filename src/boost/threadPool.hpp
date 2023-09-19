#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <vector>
#include "common/common.hpp"

namespace thread_demo {
    using namespace boost;
    /**
     * 单 context 多 thread
     */
    class ThreadPool {
    public:
        explicit ThreadPool(std::size_t threadCount) : thread_pool(threadCount) {
            for (int i = 0; i < threadCount; ++i) {
                asio::post(thread_pool, [this]() {
                    io_context.run();
                });
            }
        }

        template<typename F, typename... Args>
        void post(F &&f, Args &&... args) {
            std::function<void(Args...)> func(std::forward<F>(f));
            asio::post(io_context, func, std::forward<Args>(args)...);
        }

    private:
        asio::io_context io_context;
        asio::thread_pool thread_pool;
        asio::executor_work_guard<asio::io_context::executor_type> guard = asio::make_work_guard(io_context);
    };

    /**
     * 多 context 多 thread
     */
    class ThreadPool2 {
    public:
        using IOContext = boost::asio::io_context;
        using Work = boost::asio::io_context::work;
        using WorkPtr = std::unique_ptr<Work>;

        explicit ThreadPool2(std::size_t size) : io_context_(size), works_(size), nextIOContext_(0) {
            for (std::size_t i = 0; i < size; i++)
                works_[i] = std::make_unique<Work>(io_context_[i]);

            for (auto & ctx : io_context_)
                threads_.emplace_back([this, &ctx]() {
                    ctx.run();
                });
        }

        ThreadPool2(const ThreadPool2 &) = delete;

        ThreadPool2 &operator=(const ThreadPool2 &) = delete;

        boost::asio::io_context &getIOContext() {
            auto &service = io_context_[nextIOContext_++];
            if (nextIOContext_ == io_context_.size())
                nextIOContext_ = 0;
            return service;
        }

        void stop() {
            for (auto &work: works_)
                work.reset();

            for (auto &t: threads_)
                t.join();
        }

    private:
        std::vector<IOContext> io_context_;
        std::vector<WorkPtr> works_;
        std::vector<std::thread> threads_;
        std::size_t nextIOContext_;
    };

    void f1() {
        std::cout << "void func" << std::endl;
    }
    void test() {
        ThreadPool pool(5);
        for (int i = 0; i < 10; ++i) {
            pool.post([i] {
                std::this_thread::sleep_for(std::chrono::milliseconds(common::random(100, 1000)));
                std::cout << std::this_thread::get_id() << ".task." << i << std::endl;
            });
        }
        pool.post(f1);

        //ThreadPool2 pool2(5);
        //for (int i = 0; i < 10; ++i) {
        //    asio::post(pool2.getIOContext(), [i] {
        //        std::this_thread::sleep_for(std::chrono::milliseconds(common::random(100, 1000)));
        //        std::cout << std::this_thread::get_id() << ".task1." << i << std::endl;
        //    });
        //}
        //pool2.stop();


        //asio::thread_pool thread_pool(5);
        //for (int i = 0; i < 10; ++i) {
        //    asio::post(thread_pool, [i] {
        //        std::this_thread::sleep_for(std::chrono::milliseconds(common::random(100, 1000)));
        //        std::cout << std::this_thread::get_id() << ".taskaa" << i << std::endl;
        //    });
        //}
        //thread_pool.join();
    }
}
