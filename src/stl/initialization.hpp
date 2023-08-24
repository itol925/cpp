
#include <iostream>

namespace stl {
    namespace init {
        namespace { // 常量初始化
            struct S {
                const static int c;     // 这里必须是 const，因为
            };
            const int const_d = 10 * S::c; // 非常量表达式：S::c 此前无初始化器，此初始化发生晚于常量初始化
            const int S::c = 5;      // 常量初始化，保证首先发生。注：这句比上面一句更早执行
        }

        namespace { // 零初始化。 存储于程序的 .bss 段
            double f[3];    // 零初始化为三个 0.0
            int *p;         // 零初始化为空指针值
            std::string s;  // 零初始化为不确定值再默认初始化为 ""
        }

        void init() {
            using namespace std;

            std::cout << "-- test init --" << std::endl;

            //std::string s1{};   // 值初始化
            std::string s2("hello s2");    // 直接初始化
            std::string s3 = "hello s3";    // 复制初始化
            //std::string s4 {'h', 'e', 'l', 'l', 'e', ' ', 's', '4'};  // 列表初始化
            char arr[3] = {'a', 'b'};    // 聚合初始化
            char &c = arr[0];   // 引用初始化

            std::cout << "常量初始化d:" << const_d << std::endl;
            std::cout << "零初始化f:" << f[0] << std::endl;

            int *a = new int(3); // 动态初始化
            std::cout << "动态初始化 a：" << *a << std::endl;
            delete a;
        }
    }
}