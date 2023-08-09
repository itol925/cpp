#include <iostream>
#include <chrono>

namespace stl {
    namespace chrono_demo {
        // *chrono 主要有 3 块内容
        // 1）time point：时间点，表示具体的某一个时刻
        // 2）duration：时长，表示一个时间间隔
        // 3）clock：钟，表示当前的系统时钟

        // ref:https://zhuanlan.zhihu.com/p/414702182

        void test() {
            using namespace std::chrono;

            // 基于 system_clock 进行计时
            const time_point<system_clock> now = system_clock::now();
            std::cout << "1970年1月1日到现在的 微秒数：" << now.time_since_epoch().count() << std::endl;
            // 基于 steady_clock
            time_point now2 = steady_clock::now();
            std::cout << "1970年1月1日到现在的 微秒数：" << now2.time_since_epoch().count() << std::endl;

            // time_point 转换
            time_point<system_clock, milliseconds> now_in_mill_seconds = time_point_cast<seconds>(now);
            std::cout << "1970年1月1日到现在的 毫秒数：" << now_in_mill_seconds.time_since_epoch().count() << std::endl;
            time_point<system_clock, seconds> now_in_seconds = time_point_cast<seconds>(now);
            std::cout << "1970年1月1日到现在的 秒数：" << now_in_seconds.time_since_epoch().count() << std::endl;
            // add
            duration<int> duration_sec(100); // 100 秒。注：计时单位默认为 秒
            auto tp_add = now_in_seconds + duration_sec;
            std::cout << "1970年1月1日到现在的 秒数+100秒：" << tp_add.time_since_epoch().count() << std::endl;

            // 时长
            duration<int> d_sec(100); // 100 秒。注：计时单位默认为 秒
            duration<int, std::ratio<1, 1>> d_sec2(100); // 表示100秒。ratio<1, 1>表示计时单位为1秒
            duration<int, std::ratio<1, 1000>> d_mill_sec(100); // 表示100毫秒，即0.1秒。计时单位为 1/1000 秒，即毫秒
            duration<int, std::ratio<60, 1>> d_min(100); // 表示100分钟。计时单位为 60/1 秒，即分钟
            duration<int, std::ratio<3600, 1>> d_hour(100); // 表示100小时。计时单位为 3600/1 秒，即小时
            // 时长用法
            typedef duration<int, std::ratio<60, 1>> minute_type;
            typedef duration<int, std::ratio<3600, 1>> hour_type;
            minute_type m(30); // 30分钟
            std::cout << "m=" << m.count() << " minutes" << std::endl;
            std::cout << "d1=" << d_sec.count() << " seconds" << std::endl;
            // duration 转换
            hour_type hour(1);
            minute_type m2 = duration_cast<minute_type>(hour);
            std::cout << "1 hour = " << m2.count() << " minutes" << std::endl;
            // duration 相加。注：会自动转换成小单位的 duration
            auto d_sum = d_min + d_sec;
            std::cout << d_min.count() << " minutes + " << d_sec.count() << " seconds = " << d_sum.count() << " seconds" << std::endl;


        }
    }
}
