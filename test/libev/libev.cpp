//
// Created by Yinglong Pan on 2024/11/21.
//
#include "io/libev.hpp"
#include "gtest/gtest.h"

TEST(LibEV, CallOnce) {
    struct ev_loop *loop = ev_default_loop(0);
    ev_demo::init_timer_delay_call_once(loop);
    std::cout << "ev_loop.." << std::endl;
    ev_run(loop, 0);
}
TEST(LibEV, CallRepeat) {
    struct ev_loop *loop = ev_default_loop(0);
    ev_demo::init_timer_repeat_call(loop);
    std::cout << "ev_loop.." << std::endl;
    // 启动循环 loop
    ev_run(loop, 0);
}
TEST(LibEV, Watcher) {
    struct ev_loop *loop = ev_default_loop(0);
    ev_demo::init_io_watcher(loop);
    std::cout << "ev_loop.." << std::endl;
    // 启动循环 loop
    ev_run(loop, 0);
}
TEST(LibEV, Signal) {
    struct ev_loop *loop = ev_default_loop(0);
    ev_demo::init_signal(loop);
    std::cout << "ev_loop.." << std::endl;
    ev_run(loop, 0);
}