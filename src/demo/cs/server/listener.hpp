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
                auto connection = std::make_unique<Connection>(ctx);
                auto key = connection.get();
                acceptor.async_accept(connection->get_socket(), cti::use_continuable)
                    .then([this, key]() {
                        handle_accept_connect(key);
                    }).fail([this, key] () {
                        handle_accept_error(key);
                    });
                conMap.insert(std::make_pair(std::move(key), std::move(connection)));
            }
        private:
            void handle_accept_connect(Connection* key) {
                auto iter = conMap.find(key);
                if (iter == conMap.end()) {
                    std::cout << "not found connection" << std::endl;
                    return;
                }
                iter->second->async_start();
            }
            void handle_accept_error(Connection* key) {
                std::cout << "server:error!" << std::endl;
            }

        private:
            asio::ip::tcp::endpoint endpoint;
            asio::ip::tcp::acceptor acceptor;
            asio::io_context& ctx;
            std::map<Connection*, std::unique_ptr<Connection>> conMap;
        };
    }
}
#endif