#ifndef DEMO_CS_TEST_H_H
#define DEMO_CS_TEST_H_H

#include <iostream>
#include "client/client.hpp"
#include "server/server.hpp"

namespace demo {
    namespace cs {
        void test() {
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

#endif