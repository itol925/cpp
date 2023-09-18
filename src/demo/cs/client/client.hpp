#ifndef DEMO_CS_CLIENT_H_H
#define DEMO_CS_CLIENT_H_H

#include <iostream>
#include <boost/asio.hpp>
#include "../common/protocol.hpp"

namespace demo {
    namespace cs {
        using namespace boost;

        class Client {
        public:
            Client() : socket(io_context) {}

            void start(std::string &ip, int port) {
                auto endpoint = asio::ip::tcp::endpoint(asio::ip::address::from_string(ip), port);
                std::cout << "put your cmd:";
                do {
                    std::string cmd;
                    std::cin >> cmd;
                    if (cmd == "quit") {
                        break;
                    } else if (cmd == "con") {
                        socket.connect(endpoint);
                        std::cout << "connect success" << std::endl;
                    } else if (cmd == "discon") {
                        if (!socket.is_open()) {
                            std::cout << "not connect" << std::endl;
                            continue;
                        }
                        socket.close();
                    } else {
                        if (!socket.is_open()) {
                            std::cout << "not connect" << std::endl;
                            continue;
                        }
                        send_request(cmd);
                        read_response();
                    }
                } while (true);
            }

        private:
            asio::io_context io_context;
            asio::ip::tcp::socket socket;

            void send_request(std::string &body) {
                std::vector<asio::const_buffer> buffers;
                std::size_t body_size = body.size();
                std::cout << "client: write request head:" << body_size << std::endl;
                buffers.emplace_back(asio::buffer(&body_size, protocol::HEAD_SIZE));
                std::cout << "client: write request body:'" << body << "'" << std::endl;
                buffers.emplace_back(asio::buffer(body));
                asio::write(socket, buffers);
            }

            void read_response() {
                std::array<char, 32> buf{0};
                // read head
                std::cout << "client:try read.." << std::endl;
                asio::read(socket, asio::buffer(buf, protocol::HEAD_SIZE));
                std::size_t body_size = static_cast<unsigned char>(buf[0]);
                std::cout << "client: read response head:" << body_size << std::endl;
                // read body
                asio::read(socket, asio::buffer(buf, body_size));
                std::cout << "client: read response body:'" << buf.data() << "'" << std::endl;
            }
        };
    }
}
#endif