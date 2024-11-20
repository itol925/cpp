#include <asio.hpp>
#include <iostream>

namespace asio_demo::io_socket {
    void test_connect() {
        asio::io_context io_context;
        asio::ip::tcp::socket socket(io_context);
        asio::ip::tcp::endpoint endpoint(asio::ip::address::from_string("110.242.68.66"), 80);
        socket.async_connect(endpoint, [](const std::error_code &ec) {
            if (!ec) {
                std::cout << "Connect success" << std::endl;
            }
        });
        io_context.run();
    }

    void test_connect2() {
        asio::io_context io_context;
        asio::ip::tcp::socket socket(io_context);
        asio::ip::tcp::resolver resolver(io_context);
        asio::connect(socket, resolver.resolve("www.baidu.com", "80"));
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
        asio::error_code ec;
        //max_listen_connections: 待处理连接队列的最大长度。
        //此函数将套接字接受器置于可以接受新连接的状态。
        acceptor.listen(asio::socket_base::max_listen_connections, ec);
        if (!ec) {
            std::cout << "listen success" << std::endl;
        }
        io_context.run();
    }

    using asio::ip::tcp;

    void start_a_server() {
        asio::io_context io_context;
        auto endpoint = tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 12345);
        tcp::acceptor acceptor(io_context, endpoint);
        tcp::socket server_socket(io_context);
        acceptor.async_accept(server_socket, [](const asio::error_code &error) {
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
        std::thread server_t([] {
            start_a_server();
        });
        // start a client
        asio::io_context io_context;
        tcp::socket client_socket(io_context);
        auto endpoint = tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 12345);
        client_socket.async_connect(endpoint, [](const asio::error_code &error) {
            if (!error) {
                std::cout << "client:connect success" << std::endl;
            }
        });
        io_context.run();

        std::string body = "hello world!";
        std::size_t body_size = body.size();
        std::array<char, sizeof(std::size_t)> header{0};
        std::memcpy(&header[0], &body_size, sizeof body_size);
        std::cout << "client: write msg head" << std::endl;
        asio::write(client_socket, asio::buffer(header));
        std::cout << "client: write msg body" << std::endl;
        asio::write(client_socket, asio::buffer(body));
        server_t.join();
    }
}