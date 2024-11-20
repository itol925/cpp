#include <asio.hpp>
#include <iostream>

namespace asio_demo::thread_pool {
    /**
     * 单 context 多 thread
     */
    class ThreadPoolSingleContext {
    public:
        explicit ThreadPoolSingleContext(std::size_t threadCount) : thread_pool(threadCount) {
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
    class ThreadPoolMultiContext {
    public:
        explicit ThreadPoolMultiContext(std::size_t size) : io_context_(size), works_(size), next_io_context_(0) {
            for (std::size_t i = 0; i < size; i++)
                works_[i] = std::make_unique<asio::io_context::work>(io_context_[i]);

            for (auto & ctx : io_context_)
                threads_.emplace_back([this, &ctx]() {
                    ctx.run();
                });
        }

        ThreadPoolMultiContext(const ThreadPoolMultiContext &) = delete;

        ThreadPoolMultiContext &operator=(const ThreadPoolMultiContext &) = delete;
        void stop() {
            for (auto &work: works_)
                work.reset();

            for (auto &t: threads_)
                t.join();
        }
        template<typename F, typename... Args>
        void post(F &&f, Args &&... args) {
            std::function<void(Args...)> func(std::forward<F>(f));
            asio::post(getIOContext(), func, std::forward<Args>(args)...);
        }

    private:
        asio::io_context &getIOContext() {
            auto &service = io_context_[next_io_context_++];
            if (next_io_context_ == io_context_.size())
                next_io_context_ = 0;
            return service;
        }
    private:
        std::vector<asio::io_context> io_context_;
        std::vector<std::unique_ptr<asio::io_context::work>> works_;
        std::vector<std::thread> threads_;
        std::size_t next_io_context_;
    };
}
