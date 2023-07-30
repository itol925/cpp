#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <chrono>

namespace boost_demo {
    using namespace boost;
    namespace io_context {
        /* io_context 成员函数
         * run：运行 io_context 对象的事件处理循环，直到所有异步操作都完成或 stop 函数被调用。
         * stop：停止 io_context 对象的事件处理循环。
         * stopped：判断 io_context 对象是否已停止。
         * restart：重启 io_context 对象，以便再次运行事件处理循环。
         * poll：运行 io_context 对象的事件处理循环，以执行所有就绪的处理程序。
         * poll_one：运行 io_context 对象的事件处理循环，以执行一个就绪的处理程序。
         * get_executor：获取与 io_context 对象关联的执行器
         * run_for：运行 io_context 对象的事件处理循环，直到所有异步操作都完成、stop 函数被调用或指定的持续时间已过。
         * run_one：运行 io_context 对象的事件处理循环，以执行最多一个处理程序。
         * run_one_for：运行 io_context 对象的事件处理循环，直到执行了最多一个处理程序、stop 函数被调用或指定的持续时间已过。
         * run_one_until：运行 io_context 对象的事件处理循环，直到执行了最多一个处理程序、stop 函数被调用或指定的时间已过。
         * run_until：运行 io_context 对象的事件处理循环，直到所有异步操作都完成、stop 函数被调用或指定的时间已过。
         * */
        void handler() {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << "task1 done" << std::endl;
        }

        void test() {
            asio::io_context io_context;
            io_context.post(handler);

            io_context.post([]{
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "task2 done" << std::endl;
            });
            std::cout << "test io context.." << std::endl;
            // 注：io_context 会依次串行调用 task1, task2，执行完后，run 返回
            io_context.run();
            std::cout << "test io context done" << std::endl;
        }

        void test2() {
            asio::io_context io_context;
            io_context.post([]{
                std::cout << "task1 done" << std::endl;
            });
            io_context.post([]{
                std::cout << "task2 done" << std::endl;
            });
            // work_guard 给 io_context 任务数加 1，所以只要 work_guard 不 reset，io_context.run 是不会返回的。相当于 hold 住了 io_context
            auto work_guard = asio::make_work_guard(io_context);

            std::thread t([&io_context] {
                std::cout << "io_context run.." << std::endl;
                io_context.run();
                std::cout << "io_context run done" << std::endl;
            });

            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "work reset" << std::endl;
            work_guard.reset(); // 允许 io_context.run 返回
            t.join();
        }

        void test3() {
            asio::io_context io_context;
            io_context.post([]{
                std::cout << "task done" << std::endl;
            });
            io_context.post([]{
                std::cout << "task2 done" << std::endl;
            });
            asio::io_context::work work(io_context); // work 析构时，允许 io_context.run 返回
            std::cout << "poll 1" << std::endl;
            io_context.poll();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "poll 2" << std::endl;
            io_context.poll();
        }

        void test4() {
            // io_context 被多个线程执行 run 的情况
            asio::io_context io;

            io.post([] {
                std::cout << "Hello from thread " << std::this_thread::get_id() << "\n";
            });
            io.post([] {
                std::cout << "Hello from thread " << std::this_thread::get_id() << "\n";
            });

            std::thread t1([&io] {
                io.run();
                std::cout << "io done " << std::this_thread::get_id() << "\n";
            });
            std::thread t2([&io] {
                io.run();
                std::cout << "io done " << std::this_thread::get_id() << "\n";
            });

            t1.join();
            t2.join();
        }
    }

    namespace io_socket {
        void connect_handler(const std::error_code& ec){
            if(!ec) {
                std::cout << "Connect success" << std::endl;
            }
        }

        void test_connect() {
            asio::io_context io_context;
            asio::ip::tcp::socket socket(io_context);
            asio::ip::tcp::endpoint endpoint(asio::ip::address::from_string("110.242.68.66"), 80);
            socket.async_connect(endpoint, connect_handler);
            io_context.run();
        }

        void test_dns() {
            asio::io_context io;
            asio::ip::tcp::resolver resolver(io);

            asio::ip::tcp::resolver::query query("www.baidu.com", "http");
            asio::ip::tcp::resolver::iterator it = resolver.resolve(query);

            for (; it != asio::ip::tcp::resolver::iterator(); ++it) {
                std::cout << "ip:" << it->endpoint() << "\n";
            }
        }

        void test_acceptor() {
            asio::io_context io_context;
            asio::ip::tcp::acceptor acceptor(io_context);
            asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), 8888);
            //此函数打开套接字接受器，以便它使用指定的协议。
            acceptor.open(endpoint.protocol());
            acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
            //将接受器绑定到给定的本地端点。
            acceptor.bind(endpoint);
            system::error_code ec;
            //max_listen_connections: 待处理连接队列的最大长度。
            //此函数将套接字接受器置于可以接受新连接的状态。
            acceptor.listen(asio::socket_base::max_listen_connections, ec);
            if(!ec) {
                std::cout << "listen success" << std::endl;
            }
            io_context.run();
        }
    }

    namespace cs {
        using asio::ip::tcp;

        void start_a_server() {
            asio::io_context io_context;
            auto endpoint = tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 12345);
            tcp::acceptor acceptor(io_context, endpoint);
            tcp::socket server_socket(io_context);
            acceptor.async_accept(server_socket, [](const system::error_code& error) {
                if (!error) {
                    std::cout << "server: new connect incoming" << std::endl;
                }
            });
            std::cout << "server ready" << std::endl;
            io_context.run();

            std::array<char, 32> buf{0};
            // read head
            asio::read(server_socket, asio::buffer(buf, sizeof(std::size_t)));
            std::size_t body_size = static_cast<unsigned char>(buf[0]);
            std::cout << "server: read msg head:" << body_size << std::endl;
            // read body
            asio::read(server_socket, asio::buffer(buf, body_size));
            std::cout << "server: read msg body:" << buf.data() << std::endl;
        }
        void test_cs() {
            std::thread server_t([]{
                start_a_server();
            });
            // start a client
            asio::io_context io_context;
            tcp::socket client_socket(io_context);
            auto endpoint = tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 12345);
            client_socket.async_connect(endpoint, [](const system::error_code& error) {
                if (!error) {
                    std::cout << "client:connect success" << std::endl;
                }
            });
            io_context.run();

            std::string body = "hello world!";
            std::size_t body_size = body.size();
            std::array<char, sizeof(std::size_t)> buf{0};
            std::memcpy(&buf[0], &body_size, sizeof body_size);
            std::cout << "client: write msg head" << std::endl;
            asio::write(client_socket, asio::buffer(buf));
            std::cout << "client: write msg body" << std::endl;
            asio::write(client_socket, asio::buffer(body));
            server_t.join();
        }
    }
    // ref:https://zhuanlan.zhihu.com/p/583533338
    // ref:https://blog.csdn.net/hezhanran/article/details/110665606
    // ref:https://zhuanlan.zhihu.com/p/179070263

    void test_io() {
        //io_context::test4();

        //io_socket::test_connect();
        //io_socket::test_dns();
        //io_socket::test_acceptor();

        cs::test_cs();
    }
}