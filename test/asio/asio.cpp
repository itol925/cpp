//
// Created by Yinglong Pan on 2024/11/15.
//
#include <gtest/gtest.h>
#include "asio_demo/io_context.hpp"
#include "asio_demo/io_socket.hpp"
#include "asio_demo/timer.hpp"
#include "asio_demo/signal.hpp"
#include "asio_demo/thread_pool.hpp"
#include "common/common.hpp"

TEST(AsioTest, TestPost) {
    asio_demo::io_context::test_post();
}

TEST(AsioTest, TestPostWithGuard) {
    asio_demo::io_context::test_post_work_guard();
}

TEST(AsioTest, TestPoll) {
    asio_demo::io_context::test_poll();
}

TEST(AsioTest, TestPollWithMultiThread) {
    asio_demo::io_context::test_poll_by_multi_thread();
}

TEST(AsioTest, TestConnect) {
    asio_demo::io_socket::test_connect();
}

TEST(AsioTest, TestDNS) {
    asio_demo::io_socket::test_dns();
}

TEST(AsioTest, TestAcceptor) {
    asio_demo::io_socket::test_acceptor();
}

TEST(AsioTest, TestCS) {
    asio_demo::io_socket::test_cs();
}

TEST(AsioTest, TestWait) {
    asio_demo::timer::test_wait();
}

TEST(AsioTest, TestAsyncWait) {
    asio_demo::timer::test_async_wait();
}

TEST(AsioTest, TestSignal) {
    asio_demo::signal::test();
}

TEST(AsioTest, ThreadPool) {
    asio_demo::thread_pool::ThreadPoolSingleContext thread_pool(5);
    std::cout << "start test.." << std::endl;
    thread_pool.post([](){
        std::this_thread::sleep_for(std::chrono::milliseconds(common::random(1000, 5000)));
        std::cout << "test thread with single context" << std::endl;
    });

    for (int i = 0; i < 5; ++i) {
        thread_pool.post([i](){
            std::this_thread::sleep_for(std::chrono::milliseconds(common::random(1000, 5000)));
            std::cout << "test thread with single context " << i << std::endl;
        });
    }
}

TEST(AsioTest, ThreadPool2) {
    asio_demo::thread_pool::ThreadPoolMultiContext thread_pool(5);
    std::cout << "start test.." << std::endl;

    for (int i = 0; i < 5; ++i) {
        thread_pool.post([i](){
            std::this_thread::sleep_for(std::chrono::milliseconds(common::random(1000, 5000)));
            std::cout << "test thread with single context " << i << std::endl;
        });
    }

    thread_pool.stop();
}