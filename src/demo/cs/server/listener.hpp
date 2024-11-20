#ifndef DEMO_CS_LISTENER_H_H
#define DEMO_CS_LISTENER_H_H

#include <iostream>
#include <map>
#include "continuable/continuable.hpp"
#include "asio.hpp"
#include "connection.hpp"
using namespace cti;
using namespace std;
namespace demo {
    namespace cs {
        class Listener {
        public:
            Listener(asio::io_context &ctx, std::string &ip, int port)
                    : ctx(ctx), endpoint(asio::ip::tcp::endpoint(asio::ip::address::from_string(ip), port)),
                      acceptor(ctx, endpoint) {}

            void async_start() {
                std::cout << "server async start" << std::endl;
                auto connection = std::make_unique<Connection>(ctx);
                auto key = connection.get();
                acceptor.async_accept(connection->get_socket(), [this, key](const asio::error_code &error) {
                    if (!error) {
                        handle_accept_connect(key);
                        async_start();
                    } else {
                        handle_accept_error(key);
                    }
                });
                // todo add lock
                conMap.insert(std::make_pair(key, std::move(connection)));
            }

        private:
            void handle_accept_connect(Connection *key) {
                auto iter = conMap.find(key);
                if (iter == conMap.end()) {
                    std::cout << "not found connection" << std::endl;
                    return;
                }
                iter->second->async_start().then([this, key] {
                    handle_accept_connect(key);
                }).fail([this, key](const std::exception_ptr &ep) {
                    try {
                        std::rethrow_exception(ep);
                    } catch (const std::exception &e) {
                        std::cout << "connection exception: " << e.what() << std::endl;
                    }
                    handle_accept_error(key);
                });
            }

            void handle_accept_error(Connection *key) {
                conMap.erase(key);
            }

        private:
            asio::ip::tcp::endpoint endpoint;
            asio::ip::tcp::acceptor acceptor;
            asio::io_context &ctx;
            std::map<Connection *, std::unique_ptr<Connection>> conMap;
        };
    }
}
#endif