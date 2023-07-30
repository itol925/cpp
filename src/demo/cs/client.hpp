#ifndef DEMO_CS_CLIENT_H_H
#define DEMO_CS_CLIENT_H_H

#include <iostream>
#include <continuable/external/asio.hpp>
#include <boost/asio.hpp>

namespace demo {
    namespace cs {
        using namespace boost;
        class Client {
        public:
            void start(std::string& ip, int port) {
                asio::io_context io_context;
                asio::ip::tcp::socket client_socket(io_context);
                auto endpoint = asio::ip::tcp::endpoint(asio::ip::address::from_string(ip), port);

                std::cout << "put your cmd:";
                do {
                    std::string cmd;
                    std::cin >> cmd;
                    if (cmd == "quit") {
                        break;
                    } else if (cmd == "con") {
                        client_socket.connect(endpoint);
                        std::cout << "connect success" << std::endl;
                    } else if (cmd == "discon") {
                        if (!client_socket.is_open()) {
                            std::cout << "not connect" << std::endl;
                            continue;
                        }
                        client_socket.close();
                    } else {
                        if (!client_socket.is_open()) {
                            std::cout << "not connect" << std::endl;
                            continue;
                        }
                        send_msg(cmd, client_socket);
                    }
                } while (true);
            }
        private:
            void send_msg(std::string& body, asio::ip::tcp::socket& socket) {
                std::size_t body_size = body.size();
                std::array<char, sizeof(std::size_t)> buf{0};
                std::memcpy(&buf[0], &body_size, sizeof body_size);
                std::cout << "client: write msg head" << std::endl;
                asio::write(socket, asio::buffer(buf));
                std::cout << "client: write msg body" << std::endl;
                asio::write(socket, asio::buffer(body));
            }
        };
    }
}
#endif