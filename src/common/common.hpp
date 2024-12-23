#include <iostream>
#include <type_traits>
#include <string>
#include <chrono>
#include <thread>

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

    /*
     * 打印数组
     */
    // 基础模板（默认情况）
    template<typename T>
    struct is_vector : std::false_type {};

    // 特化模板（对于 std::vector<T, Allocator>）
    template<typename T, typename Allocator>
    struct is_vector<std::vector<T, Allocator>> : std::true_type {};

    template<typename T>
    std::string array_to_string(const std::vector<T> &arr) {
        std::string str = "[";
        for (int i = 0; i < arr.size(); i++) {
            if constexpr (is_vector<T>::value) {
                str += array_to_string(arr[i]);
            } else {
                str += std::to_string(arr[i]);
            }
            if (i != arr.size() - 1) str += ", ";
        }
        str += "]";
        return str;
    }


}