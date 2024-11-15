#include <asio.hpp>
#include <iostream>

namespace asio_demo {
    namespace signal {
        void test() {
            asio::io_context io;
            asio::signal_set signals(io, SIGINT, SIGTERM);
            signals.async_wait([](const asio::error_code& error, int signal_number) {
                if (!error) {
                    std::cout << "Received signal: " << signal_number << std::endl;
                }
            });
        }
    }
}