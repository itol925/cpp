#ifndef DEMO_CS_CONNECTION_H_H
#define DEMO_CS_CONNECTION_H_H

#include <iostream>
#include "continuable/continuable.hpp"
#include "asio.hpp"
#include "listener.hpp"
#include "handler.hpp"
#include "common/protocol.hpp"

namespace demo::cs {
        using namespace boost;

        class Connection {
        public:
            explicit Connection(asio::io_context &ctx)
                    : socket(asio::make_strand(ctx)) {}

            asio::ip::tcp::socket &get_socket() {
                return socket;
            }

            cti::continuable<std::size_t> async_start() {
                return async_read_request().then([this](std::string request_body) {
                    return async_handle_request(request_body);
                }).then([this](std::string response_body) {
                    return async_write_response(response_body);
                }).fail([](const std::exception_ptr &ep) {
                    return cti::make_exceptional_continuable<std::size_t>(ep);
                });
            }

        private:
            cti::continuable<std::string> async_read_request() {
                std::error_code ec;
                socket.read_some(asio::buffer(buf, protocol::HEAD_SIZE), ec);
                if (ec) {
                    auto ptr = std::make_exception_ptr(std::logic_error("read head failed!"));
                    return cti::make_exceptional_continuable<std::string>(ptr);
                }
                std::size_t body_size = static_cast<unsigned char>(buf[0]);
                std::cout << "server:read request head:" << body_size << std::endl;
                socket.read_some(asio::buffer(buf, body_size), ec);
                if (ec) {
                    auto ptr = std::make_exception_ptr(std::logic_error("read body failed!"));
                    return cti::make_exceptional_continuable<std::string>(ptr);
                }
                std::cout << "server:read request body:'" << buf.data() << "'" << std::endl;
                return cti::make_ready_continuable(buf.data());
            }

            cti::continuable<std::string> async_handle_request(std::string &request_body) {
                std::string response_body = handler.handle_request(request_body);
                std::cout << "server:handle request and response:'" << response_body << "'" << std::endl;
                return cti::make_ready_continuable(response_body);
            }

            cti::continuable<std::size_t> async_write_response(std::string &response_body) {
                std::vector<asio::const_buffer> buffers;
                std::size_t body_size = response_body.size();
                buffers.emplace_back(asio::buffer(&body_size, protocol::HEAD_SIZE));
                std::cout << "server:write response head:" << body_size << std::endl;
                buffers.emplace_back(asio::buffer(response_body));
                std::cout << "server:write response body:'" << response_body << "'" << std::endl;
                std::error_code ec;
                std::size_t write_len = socket.write_some(buffers, ec);
                if (ec) {
                    auto ptr = std::make_exception_ptr(std::logic_error("write response failed!"));
                    return cti::make_exceptional_continuable<std::size_t>(ptr);
                }
                return cti::make_ready_continuable(write_len);
            }

        private:
            Handler handler;
            asio::ip::tcp::socket socket;
            std::array<char, 32> buf{0};
        };
    }
#endif