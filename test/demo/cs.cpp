//
// Created by Yinglong Pan on 2024/11/20.
//
#include <iostream>
#include "client/client.hpp"
#include "server/server.hpp"
using namespace demo::cs;

int main() {
    std::string ip = "127.0.0.1";
    int port = 10086;

    Server server;
    std::thread t([&server, &ip, port] {
        server.start(ip, port);
    });

    Client client;
    client.start(ip, port);
}