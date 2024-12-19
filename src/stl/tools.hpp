#include <iostream>

namespace stl::tools {
    std::optional<std::string> create_ref(bool b) {
        if (b) {
            return "abc";
        } else {
            return {};
        }
    }

    void test() {
        int p = 1;
        auto int_plus = std::plus<int>(); // 相当于调用了 operator+() 函数
        std::cout << "std::plus(1, 1)=" << int_plus(p, 1) << std::endl;

        std::string s = "abc", s2 = "abc", s3 = "bde";
        auto hs = std::hash<std::string>{}; // 构造一个 hash string 的对象
        std::cout << "hash(s)=" << hs(s) << ",hash(s2)=" << hs(s2) << ",hash(s3)=" << hs(s3) << std::endl;

        auto os = create_ref(true);
        std::cout << "os:" << (os.has_value() ? os.value() : "no_value") << std::endl;
        auto os2 = create_ref(false);
        std::cout << "os2:" << (os2.has_value() ? os2.value() : "no_value") << std::endl;
    }
}