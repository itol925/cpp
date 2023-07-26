#include <iostream>

namespace stl {
    namespace storage {
        // 存储说明符
        // auto：自动存储，默认存储类型
        // register：自动存储，寄存器存储，c++11已弃用
        // static：声明类成员时：静态成员；声明对象时：静态存储；内部连接
        // extern：外部连接。注：所有 extern 对象都具有静态或线程存储期
        // thread_local：线程存储。能与 static 或 extern 结合，以分别指定内部或外部连接

        // 存储期
        // 自动存储期：对象的作用块开始时分配，结束时销毁。分布：非 extern、static、thread_local 的局部对象
        // 静态存储期：程序开始时分配，结束时销毁。分布：全局对象、带 extern、static 的对象
        // 线程存储期：线程开始时分配，结束时销毁。分布：带 thread_local 的对象
        // 动态存储期：new出来的对象

        // 连接
        // 表示是否能被外部引用。对象、引用、函数、类型、模板、命名空间可具有连接
        // 无连接：未显示声明 extern 的局部变量、局部类及其成员函数、块内的成员
        // 内部连接：命名空间下的 static 变量、函数、未声明 extern 的 const 成员、匿名 union 成员
        // 外部连接：除 无连接 和 内部连接 以外都是外部连接。注：外部连接也是跨语言连接，可以供其他语言访问
    }
}