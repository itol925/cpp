#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include <iostream>

ABSL_FLAG(int, port, 80, "port");
ABSL_FLAG(std::string, name, "world", "user name");

// brew instal labseil
namespace absl_demo {
    void test(int argc, char* argv[]) {
        std::vector<char*> ret = ::absl::ParseCommandLine(argc, argv);
        std::cout << "args.size:" << ret.size() << std::endl;

        int port = ::absl::GetFlag(FLAGS_port);
        std::string name = ::absl::GetFlag(FLAGS_name);
        std::cout << "port:" << port << ", name:" << name << std::endl;
    }
}