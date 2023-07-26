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

        namespace cs {
            namespace protocol {
                enum {
                    header_size = sizeof(std::size_t)
                };
            }

            void noop(const std::string &str) {
                std::cout << "noop:" << str << std::endl;
            }

            std::vector<char> build_header(const std::string &body) {
                std::vector<char> buffer(protocol::header_size);
                auto body_size = body.size();
                std::memcpy(&buffer[0], &body_size, sizeof body_size);
                return buffer;
            }

            std::size_t parse_header(const std::vector<char> &buffer) {
                return *reinterpret_cast<const std::size_t *>(&buffer[0]);
            }

            void test_cs() {
                using asio::ip::tcp;

                // Create all I/O objects.
                asio::io_context io_context;
                tcp::acceptor acceptor(io_context, tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 1234));
                tcp::socket server_socket(io_context);
                tcp::socket client_socket(io_context);

                // Connect the sockets.
                acceptor.async_accept(server_socket, std::bind(&noop, "accept"));
                client_socket.async_connect(acceptor.local_endpoint(), std::bind(&noop, "connect"));

                io_context.run();
                io_context.reset();

                //  Write a message from socket1 to socket2.
                std::string test_message = "this is a test message";
                {
                    auto header = build_header(test_message);

                    // Gather header and body into a single buffer.
                    std::array<asio::const_buffer, 2> buffers = {{
                                                                         asio::buffer(header),
                                                                         asio::buffer(test_message)
                                                                 }};

                    // Write header and body to socket.
                    std::cout << server_socket.is_open() << std::endl;
                    asio::write(server_socket, buffers);
                }

                // Read from socket2.
                {
                    std::vector<char> buffer;

                    // Read header.
                    buffer.resize(protocol::header_size);
                    asio::read(client_socket, asio::buffer(buffer));

                    // Extract body size from header, resize buffer, then read body.
                    auto body_size = parse_header(buffer);
                    buffer.resize(body_size);
                    asio::read(client_socket, asio::buffer(buffer));

                    // Verify body was read.
                    assert(std::equal(begin(buffer), end(buffer),
                                      begin(test_message)));
                    std::cout << "received: \n"
                                 "  header: " << body_size << "\n"
                                                              "  body: ";
                    std::cout.write(&buffer[0], buffer.size());
                    std::cout << std::endl;
                }
            }
        }
        // ref:https://zhuanlan.zhihu.com/p/583533338
        // ref:https://blog.csdn.net/hezhanran/article/details/110665606
    }

    void test_io() {
        //io_context::test4();

        //io_socket::test_connect();
        //io_socket::test_dns();
        //io_socket::test_acceptor();

        io_socket::cs::test_cs();
    }
}