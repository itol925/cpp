#ifndef DEMO_CS_LISTENER_H_H
#define DEMO_CS_LISTENER_H_H

#include <iostream>
#include <map>
#include <continuable/continuable.hpp>
#include <continuable/external/asio.hpp>
#include "connection.hpp"

namespace demo {
    namespace cs {
        using namespace boost;
        class Listener {
        public:
            Listener(asio::io_context& ctx, std::string& ip, int port)
                : ctx(ctx)
                , endpoint(asio::ip::tcp::endpoint(asio::ip::address::from_string(ip), port))
                , acceptor(ctx, endpoint) { }

            void async_start() {
                connection = std::make_unique<Connection>(ctx);
                acceptor.async_accept(connection->get_socket(), cti::use_continuable)
                    .then([this]() {
                        handle_accept_connect();
                    }).fail([this] () {
                        handle_accept_error();
                    }).then([this] {
                        async_start();
                    });
            }
        private:
            void handle_accept_connect() {
                connection->async_start()
                    .then([](const std::string& msg){
                        std::cout << "server:recv msg:" << msg << std::endl;
                    }).then([this] {
                        handle_accept_connect(); // 下一轮读数据
                    });
            }
            void handle_accept_error() {
                std::cout << "server:error!" << std::endl;
            }
        private:
            asio::ip::tcp::endpoint endpoint;
            asio::ip::tcp::acceptor acceptor;
            asio::io_context& ctx;
            std::unique_ptr<Connection> connection;
        };
    }
}
#endif