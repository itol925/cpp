#include <iostream>

#pragma once

namespace common {
    void sleep(int milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds (milliseconds));
    }

    /**
    * 产生[a,b)的随机数，可以使用
    * @param a
    * @param b
    * @return
    */
    int random(int a, int b) {
        return (rand() % (b - a)) + a;
    }

    /**
     * [0, 100) 之间的随机数
     * @return
     */
    int random() {
        return random(0, 100);
    }
}