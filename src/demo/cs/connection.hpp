#ifndef DEMO_CS_CONNECTION_H_H
#define DEMO_CS_CONNECTION_H_H

#include <iostream>
#include <boost/asio.hpp>
#include "listener.hpp"
#include "handler.hpp"

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
                async_read_request_head()
                    .then([this](std::size_t len) {
                        return async_read_request_body(len);
                    }).then([this](std::string request_body){
                        return async_handle_request(request_body);
                    }).then([this](std::string response) {
                        return async_write_response_head(response);
                    }).then([this](std::string response) {
                        return async_write_response_body(response);
                    }).then([this]() {
                        async_start();
                    });
            }
        private:
            cti::continuable<std::size_t> async_read_request_head() {
                asio::read(socket, asio::buffer(buf, sizeof(std::size_t)));
                std::size_t body_size = static_cast<unsigned char>(buf[0]);
                std::cout << "server:read request head:" << body_size << std::endl;
                return cti::make_ready_continuable(body_size);
            }
            cti::continuable<std::string> async_read_request_body(std::size_t len) {
                asio::read(socket, asio::buffer(buf, len));
                std::cout << "server:read request body:'" << buf.data() << "'" << std::endl;
                return cti::make_ready_continuable(buf.data());
            }
            cti::continuable<std::string> async_handle_request(std::string& body) {
                std::string response = handler.handle_request(body);
                std::cout << "server:handle request and response:'" << response << "'" << std::endl;
                return cti::make_ready_continuable(response);
            }
            cti::continuable<std::string> async_write_response_head(std::string& response) {
                std::size_t body_size = response.size();
                std::memcpy(&buf[0], &body_size, sizeof body_size);
                std::cout << "server:write response head:" << body_size << std::endl;
                asio::write(socket, asio::buffer(buf));
                return cti::make_ready_continuable(response);
            }
            cti::continuable<> async_write_response_body(std::string& response) {
                std::cout << "server:write response body:'" << response << "'" << std::endl;
                asio::write(socket, asio::buffer(response));
                return cti::make_ready_continuable();
            }
        private:
            Handler handler;
            asio::ip::tcp::socket socket;
            std::array<char, 32> buf{0};
        };
    }
}
#endif