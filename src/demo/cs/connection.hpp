#ifndef DEMO_CS_CONNECTION_H_H
#define DEMO_CS_CONNECTION_H_H

#include <iostream>
#include <boost/asio.hpp>
#include "listener.hpp"

namespace demo {
    namespace cs {
        using namespace boost;
        class Connection {
        public:
            explicit Connection(asio::io_context& ctx)
            : socket(asio::make_strand(ctx)) {}

            asio::ip::tcp::socket& get_socket() {
                return socket;
            }

            cti::continuable<std::string> async_start() {
                return async_read_head()
                    .then([this](std::size_t l) {
                        return async_read_body(l);
                    });
            }
        private:
            cti::continuable<std::size_t> async_read_head() {
                asio::read(socket, asio::buffer(buf, sizeof(std::size_t)));
                std::size_t body_size = static_cast<unsigned char>(buf[0]);
                return cti::make_ready_continuable(body_size);
            }
            cti::continuable<std::string> async_read_body(std::size_t len) {
                asio::read(socket, asio::buffer(buf, len));
                return cti::make_ready_continuable(buf.data());
            }
        private:
            asio::ip::tcp::socket socket;
            std::array<char, 32> buf{0};
        };
    }
}
#endif