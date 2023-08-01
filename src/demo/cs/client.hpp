#ifndef DEMO_CS_CLIENT_H_H
#define DEMO_CS_CLIENT_H_H

#include <iostream>
#include <continuable/external/asio.hpp>
#include <boost/asio.hpp>
#include <chrono>

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
                        quit = true;
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
                        send_request(cmd, client_socket);
                        read_response(client_socket);
                    }
                } while (true);
            }
        private:
            bool quit;
            std::array<char, 32> buf{0};
            void send_request(std::string& body, asio::ip::tcp::socket& socket) {
                std::size_t body_size = body.size();
                std::array<char, sizeof(std::size_t)> buf{0};
                std::memcpy(&buf[0], &body_size, sizeof body_size);
                std::cout << "client: write request head:" << body_size << std::endl;
                asio::write(socket, asio::buffer(buf));
                std::cout << "client: write request body:'" << body << "'" << std::endl;
                asio::write(socket, asio::buffer(body));
            }
            void read_response(asio::ip::tcp::socket& client_socket) {
                // read head
                std::cout << "client:try read.." << std::endl;
                asio::read(client_socket, asio::buffer(buf, sizeof(std::size_t)));
                //std::cout << "read_len:" << read_len << " " << sizeof(std::size_t) << std::endl;
                std::size_t body_size = static_cast<unsigned char>(buf[0]);
                std::cout << "client: read response head:" << body_size << std::endl;
                // read body
                asio::read(client_socket, asio::buffer(buf, body_size));
                std::cout << "client: read response body:'" << buf.data() << "'" << std::endl;
            }
        };
    }
}
#endif