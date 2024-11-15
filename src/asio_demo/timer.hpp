#include <asio/io_context.hpp>
#include <asio.hpp>
#include <iostream>
#include <thread>
#include <chrono>

namespace asio_demo {
    namespace timer {
        void test_wait() {
            asio::io_context io;
            std::cout << "start.." << std::endl;
            asio::steady_timer timer(io, std::chrono::seconds(5));
            timer.wait();
            std::cout << "times up\n";
        }

        void test_async_wait() {
            asio::io_context io;
            std::cout << "start.." << std::endl;
            asio::steady_timer timer(io, std::chrono::seconds(5));
            timer.async_wait([](const asio::error_code& error) {
                if (!error) {
                    std::cout << "times up\n";
                }
            });
            io.run();
        }
    }
}