#include <iostream>
#include "server.hpp"
#include "client.hpp"

namespace demo {
    namespace cs {
        void test_cs() {
            std::string ip = "127.0.0.1";
            int port = 10086;

            Server server;
            std::thread t([&server, &ip, port] {
                server.start(ip, port);
            });

            Client client;
            client.start(ip, port);
        }
    }
}