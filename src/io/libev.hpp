#include <iostream>
#include <ev.h>
#include <unistd.h>
#include <csignal>

namespace ev_demo {
    /**
     * ref: https://libev.cn/base/used.html
     * ref: https://www.cnblogs.com/dszhazha/p/4082265.html
     * ev_io        // IO读写
     * ev_timer     // 定时器
     * ev_periodic  // 周期任务
     * ev_signal    // 信号处理
     * ev_child     // 子进程状态
     * ev_stat      // 文件属性变化
     * ev_async     // 激活线程
     * ev_fork      // 开辟进程
     * ev_embed     // 嵌入式事件循环
     * ev_idle      // 每次event loop空闲触发事件
     * ev_prepare   // 每次event loop之前事件
     * ev_check     // 每次event loop之后事件
     * ev_cleanup   // event loop退出触发事件
     */

    /**
     * ev_io
     */
    namespace {
        ev_io io_watcher;
        void io_cb(struct ev_loop *loop, struct ev_io *w, int revents) {
            char buf[1024] = {0};
            ssize_t nread = read(w->fd, buf, sizeof(buf) - 1);
            if (nread < 0) {
                perror("read error");
                return;
            }
            std::cout << "read:" << buf << std::endl;

            // 停止 watcher
            // ev_io_stop(loop, w);

            // 停止所有事件
            // ev_break(loop, EVBREAK_ALL);
        }

        void init_io_watcher(struct ev_loop *loop) {
            ev_io_init(&io_watcher, io_cb, 0, EV_READ);
            ev_io_start(loop, &io_watcher);
            std::cout << "input:\n";
        }
    }

    /**
     * ev_timer
     */
    namespace {
        ev_timer timer_watcher;

        void timeout_cb(struct ev_loop *loop, struct ev_timer* w, int revents) {
            std::cout << "timeout repeat:" << w->repeat << std::endl;
            // 跳出循环 loop
            // ev_break(loop, EVUNLOOP_ONE);

            // repeat 次数 +5，重启 watcher
            w->repeat += 5;
            ev_timer_again(loop, w);
        }

        void init_timer_delay_call_once(struct ev_loop *loop) {
            // 初始化 timer watcher，2 秒后 timeout
            ev_timer_init(&timer_watcher, timeout_cb, 2, 0);
            ev_timer_start(loop, &timer_watcher);
        }

        void time_repeat_cb(struct ev_loop *loop, struct ev_timer* w, int revents) {
            std::cout << "repeat" << std::endl;
        }
        void init_timer_repeat_call(struct ev_loop *loop) {
            // 初始化 tmier watcher, 第一次 2 秒后调用 callback，后面每 1 秒 repeat 一次
            ev_timer_init(&timer_watcher, time_repeat_cb, 2, 1);
            ev_timer_start(loop, &timer_watcher);
        }
    }

    /**
     * ev_signal
     */
    namespace {
        ev_signal signal_watcher;
        void signal_cb(struct ev_loop* loop, struct ev_signal* w, int revents) {
            std::cout << "get SIGINT" << std::endl;
            ev_break(loop, EVBREAK_ALL);
        }
        // 通过 ps aux | grep test 获取 pid
        // 通过 kill -s SIGINT pid 触发
        void init_signal(struct ev_loop* loop) {
            ev_signal_init(&signal_watcher, signal_cb, SIGINT);
            ev_signal_start(loop, &signal_watcher);
        }
    }

    void test() {
        struct ev_loop *loop = ev_default_loop(0);

        // init_timer_delay_call_once(loop);
        // init_timer_repeat_call(loop);
        // init_io_watcher(loop);
        init_signal(loop);

        std::cout << "ev_loop.." << std::endl;
        // 启动循环 loop
        ev_run(loop, 0);
    }
}