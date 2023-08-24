#include <iostream>

#pragma once

namespace common {
    /**
        * 产生[a,b)的随机数，可以使用
        * @param a
        * @param b
        * @return
        */
    int random(int a, int b) {
        return (rand() % (b - a)) + a;
    }
}