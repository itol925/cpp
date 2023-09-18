#ifndef DEMO_CS_PROTOCOL_H_H
#define DEMO_CS_PROTOCOL_H_H

#include <iostream>

namespace demo {
    namespace cs {
        struct protocol {
            static const std::size_t HEAD_SIZE = sizeof(std::size_t);
        };
    }
}

#endif