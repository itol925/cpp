#ifndef DEMO_CS_SERVER_H_H
#define DEMO_CS_SERVER_H_H

#include <iostream>
#include "listener.hpp"

namespace demo {
    namespace cs {
        class Server {
        public:
            void start(std::string &ip, int port) {
                asio::io_context ctx;
                auto work_guard = asio::make_work_guard(ctx);
                Listener listener(ctx, ip, port);
                listener.async_start();
                std::cout << "server ready" << std::endl;
                ctx.run();
            }
        };
    }
}
#endif