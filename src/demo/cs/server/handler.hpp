#ifndef DEMO_CS_HANDLER_H_H
#define DEMO_CS_HANDLER_H_H

#include <iostream>
#include <continuable/continuable.hpp>
#include <continuable/external/asio.hpp>

namespace demo {
    namespace cs {
        class Handler {
        public:
            std::string handle_request(const std::string& request) {
                return "echo:" + request;
            }
        };
    }
}

#endif