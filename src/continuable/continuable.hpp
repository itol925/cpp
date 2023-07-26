#include <continuable/continuable.hpp>
#include <continuable/external/asio.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <thread>

namespace continue_demo {
    namespace install {
        // git clone https://github.com/Naios/continuable.git
        // git submodule init
        // git submodule update

        //cd continuable
        //mkdir build
        //cd build
        //cmake ..

        //make
        //sudo make install
    }

    using namespace boost;
    void test() {
        asio::io_context io_context;
        asio::post(io_context, cti::use_continuable).then([] {
            std::this_thread::sleep_for(std::chrono::seconds(5));
        });
        std::thread t([&io_context] {
            std::cout << "context start.. " << std::endl;
            io_context.run();
            std::cout << "context start end" << std::endl;
        });
        t.join();
    }
}


