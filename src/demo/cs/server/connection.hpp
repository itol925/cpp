#ifndef DEMO_CS_CONNECTION_H_H
#define DEMO_CS_CONNECTION_H_H

#include <iostream>
#include <boost/asio.hpp>
#include "listener.hpp"
#include "handler.hpp"
#include "../common/protocol.hpp"

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

            void async_start() {
                async_read_request().then([this](std::string request_body){
                    return async_handle_request(request_body);
                }).then([this](std::string response_body) {
                    return async_write_response(response_body);
                }).then([this]() {
                    async_start();
                });
            }
        private:
            cti::continuable<std::string> async_read_request() {
                asio::read(socket, asio::buffer(buf, protocol::HEAD_SIZE));
                std::size_t body_size = static_cast<unsigned char>(buf[0]);
                std::cout << "server:read request head:" << body_size << std::endl;
                asio::read(socket, asio::buffer(buf, body_size));
                std::cout << "server:read request body:'" << buf.data() << "'" << std::endl;
                return cti::make_ready_continuable(buf.data());
            }
            cti::continuable<std::string> async_handle_request(std::string& request_body) {
                std::string response_body = handler.handle_request(request_body);
                std::cout << "server:handle request and response:'" << response_body << "'" << std::endl;
                return cti::make_ready_continuable(response_body);
            }
            cti::continuable<std::size_t> async_write_response(std::string& response_body) {
                std::vector<asio::const_buffer> buffers;
                std::size_t body_size = response_body.size();
                buffers.emplace_back(asio::buffer(&body_size, protocol::HEAD_SIZE));
                std::cout << "server:write response head:" << body_size << std::endl;
                buffers.emplace_back(asio::buffer(response_body));
                std::cout << "server:write response body:'" << response_body << "'" << std::endl;
                std::size_t write_len = asio::write(socket, buffers);
                return cti::make_ready_continuable(write_len);
            }
        private:
            Handler handler;
            asio::ip::tcp::socket socket;
            std::array<char, 32> buf{0};
        };
    }
}
#endif