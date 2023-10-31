#include <iostream>
#include <complex>
#include <iomanip>
#include <utility>
#include <memory>
#include <string>
#include <algorithm>

namespace stl {
    // class 和 struct 均可用于类定义。struct 相当于 public class。
    namespace classes {
        namespace member {
            struct S {
                // 非静态成员
                int n;                // 非静态数据成员
                int &r;               // 引用类型的非静态数据成员
                int a[2] = {1, 2};    // 带默认成员初始化器的非静态数据成员 (C++11)
                std::string s, *ps;   // 两个非静态数据成员
                struct NestedS {
                    std::string s;
                } d5;                 // 具有嵌套类型的非静态数据成员
                char bit: 2;         // 2 位的位域

                // 静态成员
                inline static int n1 = 1;   // 注意，inline 静态成员可以在类中定义
                const static int n3 = 1;    // 带 const 的整形和枚举类型初始化为 常量初始化
                const static int m{2}; // C++11 起
                const static int k;

                // 以下成员也是 常量初始化
                constexpr static int arr[] = {1, 2, 3};        // OK
                constexpr static std::complex<double> n4 = {1, 2}; // OK
                // constexpr static int k; // 错误：constexpr static 要求初始化器
            };
        }

        namespace member_func {
            class C {
            public:
                // 非静态成员函数
                int mf1(); // 非静态成员函数声明
                void mf2() volatile, mf3() &&; // 可为 cv 限定或引用限定
                int mf4() const { return data; } // 可内联定义
                virtual void mf5() final; // 可为虚函数，可使用 final/override
                // 构造函数亦是成员函数
                int data;

                C() : data(12) {}

                // 成员模板
                template<typename T>
                void test(const T t);
            };

            // 注：函数后面接 volatile 表示该函数可以作用于 volatile 类型的对象。比如：
            static void test_volatile() {
                C c1;
                volatile C c2;
                c1.mf2(); // 错误：不能在非 volatile 对象上调用 volatile 成员函数
                c2.mf2(); // 正确：可以在 volatile 对象上调用 volatile 成员函数
            }


            // 注2: 函数后面接 && 表示函数对象为右值时调用。比如：
            static void test_rvalue() {
                struct S {
                    void f() &{ std::cout << "lvalue\n"; }

                    void f() &&{ std::cout << "rvalue\n"; }
                };

                S s;
                s.f();      // 调用 void f() &，输出 "lvalue"
                S().f();    // 调用 void f() &&，输出 "rvalue"
            }
        }

        namespace nested {
            int x, y;   // 全局变量
            class enclose { // 外围类
                int x;      // 注：私有成员
                static int s;
            public:
                struct inner { // 嵌套类
                    void f(int i) {
                        // x = i;   // 错误：不能不带实例地写入非静态的 enclose::x
                        int a = sizeof x;   // C++11 前错误。
                        // C++11 中 OK：sizeof 的操作数不求值，
                        // 非静态 enclose::x 的此种用法是允许的。
                        s = i;   // OK：可赋值给静态 enclose::s
                        nested::x = i;  // OK：可赋值给全局 x
                        y = i;          // OK：可赋值给全局 y
                    }

                    void g(enclose *p, int i) {
                        p->x = i; // OK：赋值给 enclose::x
                    }
                };
            };
        }

        // T()
        namespace default_constructor {
            // 以下任意一种情况出现都不会自动生成默认构造函数
            // T 拥有无默认初始化器的引用类型的成员。
            // T 拥有无用户定义默认构造函数或默认成员初始化器 (C++11 起)的 const 成员。
            // T 拥有（无默认成员初始化器） (C++11 起)的成员，其默认构造函数被弃置，或对于此构造函数有歧义或不可访问。
            // T 拥有直接基类或虚基类，其默认构造函数被弃置，或对于此构造函数有歧义或不可访问。
            // T 拥有直接基类或虚基类，其析构函数被弃置，或对于此构造函数不可访问。
            // T 是 union，其至少一个变体成员有非平凡默认构造函数，且变体成员无一拥有默认成员初始化器。
            // T 是拥有变体成员 M 的非联合类，该成员拥有非平凡默认构造函数，且包含 M 的匿名联合体的变体成员无一拥有默认成员初始化器。
            // T 为 union，且其所有变体成员均为 const。

            struct A {
                int x;

                A(int x = 1) : x(x) {} // 用户定义默认构造函数
            };

            struct B : A {  // 隐式定义 B::B()，调用 A::A()
            };
            struct C {  // 隐式定义 C::C()，调用 A::A()
                A a;
            };

            struct D : A {
                D(int y) : A(y) {} // 不会声明 D::D()，因为存在另一构造函数
            };

            struct E : A {
                E(int y) : A(y) {}

                E() = default; // 显式预置，调用 A::A()
            };

            struct F {
                int &ref;   // 引用成员
                const int c; // const 成员
                // F::F() 被隐式定义为弃置
            };

            void test() {
                A a;
                B b;
                C c;
                //  D d; // 编译错误
                E e;
                //  F f; // 编译错误
            }
        }

        // T(T&)
        namespace copy_constructor {
            // 复制构造函数是非模板构造函数，其首个形参为 T&、const T&、volatile T& 或 const volatile T&，而且要么没有其他形参，要么剩余形参均有默认值。

            // 复制构造函数的触发场景：
            // 1：直接初始化（T t1(t)）或复制初始化（T t1 = t）时，注：前提是没有被重载决议排除、没有被复制消除
            // 2：函数实参传递 f(t)
            // 3：函数返回，注：前提是没有移动构造函数

            // 以下情况编译器不会生成默认的复制构造函数
            // 1：T 拥有无法复制的非静态数据成员（拥有被弃置、不可访问或有歧义的复制构造函数）；
            // 2：T 拥有无法复制的直接或虚基类（拥有被弃置、不可访问或有歧义的复制构造函数）；
            // 3：T 拥有带被弃置或不可访问的析构函数的直接或虚基类；
            // 4：T 是联合式的类，且拥有带非平凡复制构造函数的变体成员；
            // 5：T 拥有右值引用类型的数据成员；
            // 6：T 拥有用户定义的移动构造函数或移动赋值运算符（此条件只导致隐式声明的，而非预置的复制构造函数被弃置）。

            // 什么叫平凡的复制构造函数？满足以下条件：
            // 1：它不是用户提供的（即它是隐式定义或预置的）；
            // 2：T 没有虚成员函数；
            // 3：T 没有虚基类；
            // 4：T 的每个直接基类选择的复制构造函数都是平凡的；
            // 5：T 的每个类类型（或类类型数组）的非静态成员选择的复制构造函数都是平凡的；
            // 注：平凡即类对象可以"位逐次拷贝"，即类对象 没有虚成员（包括基类的成员） 且 没有虚基类 且 所有非静态成员是平凡的 且 复制构造函数是平凡的

            struct A {
                int n;

                A(int n = 1) : n(n) {}

                A(const A &a) : n(a.n) {} // 用户定义的复制构造函数
            };

            struct B : A {
                // 隐式默认构造函数 B::B()
                // 隐式复制构造函数 B::B(const B&)
            };

            struct C : B {
                C() : B() {}

            private:
                C(const C &); // 不可复制，C++98 风格
            };

            void test() {
                A a1(7);
                A a2(a1); // 调用复制构造函数
                B b;
                B b2 = b;
                A a3 = b; // 转换到 A& 并调用复制构造函数
                volatile A va(10);
                // A a4 = va; // 编译错误

                C c;
                // C c2 = c; // 编译错误
            }
        }

        // T(T&&)
        namespace move_constructor {
            // 移动构造函数是非模板构造函数，其首个形参是 T&&、const T&&、volatile T&& 或 const volatile T&&，且无其他形参，或剩余形参均有默认值。
            // 移动构造函数的触发场景：
            // 1：用右值或亡值直接初始化（T t(std::move(t1))）或复制初始化（T t = std::move(t1)）对象时
            // 2：函数实参传递 f(std::move(t))
            // 3：函数返回。注：需要类有移动构造函数

            // 以下情况不会生成默认的移动构造函数：
            // 1：T 拥有无法移动（拥有被弃置、不可访问或有歧义的移动构造函数）的非静态数据成员；
            // 2：T 拥有无法移动（拥有被弃置、不可访问或有歧义的移动构造函数）的直接或虚基类；
            // 3：T 拥有带被弃置或不可访问的析构函数的直接或虚基类；
            // 4：T 是联合式的类，且拥有带非平凡移动构造函数的变体成员。

            // 什么是平凡的移动构造函数
            // 1：它不是用户提供的（即它是隐式定义或预置的）；
            // 2：T 没有虚成员函数；
            // 3：T 没有虚基类；
            // 4：T 的每个直接基类选择的移动构造函数都是平凡的；
            // 5：T 的每个类类型（或类类型数组）的非静态成员选择的移动构造函数都是平凡的。

            struct A {
                std::string s;
                int k;

                A() : s("test"), k(-1) {}

                A(const A &o) : s(o.s), k(o.k) { std::cout << "move failed!\n"; }

                A(A &&o) noexcept:
                        s(std::move(o.s)),       // 类类型成员的显式移动
                        k(std::exchange(o.k, 0)) // 非类类型成员的显式移动
                {}
            };

            A f(A a) {
                return a;
            }

            struct B : A {
                std::string s2;
                int n;
                // 隐式移动构造函数 B::(B&&)
                // 调用 A 的移动构造函数
                // 调用 s2 的移动构造函数
                // 并进行 n 的逐位复制
            };

            struct C : B {
                ~C() {} // 析构函数阻止隐式移动构造函数 C::(C&&)
            };

            struct D : B {
                D() {}

                ~D() {}          // 析构函数阻止隐式移动构造函数 D::(D&&)
                D(D &&) = default; // 强制生成移动构造函数
            };

            void test() {
                std::cout << "Trying to move A\n";
                A a1 = f(A()); // 按值返回时，从函数形参移动构造其目标
                std::cout << "Before move, a1.s = " << std::quoted(a1.s) << " a1.k = " << a1.k << '\n';
                A a2 = std::move(a1); // 从亡值移动构造
                std::cout << "After move, a1.s = " << std::quoted(a1.s) << " a1.k = " << a1.k << '\n';

                std::cout << "Trying to move B\n";
                B b1;
                std::cout << "Before move, b1.s = " << std::quoted(b1.s) << "\n";
                B b2 = std::move(b1); // 调用隐式移动构造函数
                std::cout << "After move, b1.s = " << std::quoted(b1.s) << "\n";

                std::cout << "Trying to move C\n";
                C c1;
                C c2 = std::move(c1); // 调用复制构造函数

                std::cout << "Trying to move D\n";
                D d1;
                D d2 = std::move(d1);
            }
        }

        // operator=(const T&)
        namespace copy_operator {
            // 复制赋值运算符是名为 operator= 的非模板非静态成员函数，它接收恰好一个 T、T&、const T&、volatile T& 或 const volatile T& 类型的形参

            // 若下列任何一项为真，则类 T 的隐式声明的复制赋值运算符被定义为弃置的：
            // 1：T 拥有用户声明的移动构造函数；
            // 2：T 拥有用户声明的移动赋值运算符。
            // 否则，它被定义为预置的。若下列任何一项为真，则类 T 的预置的复制赋值运算符被定义为弃置的：
            // 1：T 拥有非类类型（或其数组）的 const 限定的非静态数据成员；
            // 2：T 拥有引用类型的非静态数据成员；
            // 3：T 拥有无法复制赋值的非静态数据成员，或直接或虚基类（对复制赋值的重载决议失败，或选择弃置或不可访问的函数）；
            // 4：T 是联合体式的类，且拥有对应复制赋值运算符非平凡的变体成员。

            // 什么叫平凡复制赋值运算符
            // 1：它不是用户提供的（即它是隐式定义或预置的），且若它被预置，则其签名与隐式定义的相同 (C++14 前)；
            // 2：T 没有虚成员函数；
            // 3：T 没有虚基类；
            // 4：T 的每个直接基类选择的复制赋值运算符都是平凡的；
            // 5：T 的每个类类型（或类类型的数组）的非静态数据成员选择的复制赋值运算符都是平凡的；
            // 6：T 没有 volatile 限定类型的非静态数据成员。

            struct A {
                int n;
                std::string s1;

                // 用户定义的复制赋值，复制并交换形式
                A &operator=(A other) {
                    std::cout << "copy assignment of A\n";
                    std::swap(n, other.n);
                    std::swap(s1, other.s1);
                    return *this;
                }
            };

            struct B : A {
                std::string s2; // 隐式定义的复制赋值
            };

            struct C {
                std::unique_ptr<int[]> data;
                std::size_t size;

                // 非复制并交换的赋值
                C &operator=(const C &other) {
                    // 检查自赋值
                    if (&other == this)
                        return *this;
                    // 可能时复用存储
                    if (size != other.size) {
                        data.reset(new int[other.size]);
                        size = other.size;
                    }
                    std::copy(&other.data[0], &other.data[0] + size, &data[0]);
                    return *this;
                }
                // 注意：复制并交换始终导致重分配
            };

            void test() {
                A a1, a2;
                std::cout << "a1 = a2 calls ";
                a1 = a2; // 用户定义的复制赋值

                B b1, b2;
                b2.s1 = "foo";
                b2.s2 = "bar";
                std::cout << "b1 = b2 calls ";
                b1 = b2; // 隐式定义的复制赋值
                std::cout << "b1.s1 = " << b1.s1 << " b1.s2 = " << b1.s2 << '\n';
            }
        }

        // operator=(T&&)
        namespace move_operator {
            // 移动赋值运算符触发场景
            // 1：当对象出现在赋值表达式左侧，而其右侧是同类型或可隐式转换的类型的右值时

            // 下列任何一项为真，则类 T 的隐式声明或预置的移动赋值运算符被定义为弃置的：
            // 1：T 拥有 const 限定的非静态数据成员；
            // 2：T 拥有引用类型的非静态数据成员；
            // 3：T 拥有无法移动赋值（拥有被弃置、不可访问或有歧义的移动赋值运算符）的非静态数据成员；
            // 4：T 拥有无法移动赋值（拥有被弃置、不可访问或有歧义的移动赋值运算符）的直接或虚基类。

            // 当下列各项均为真时，类 T 的移动赋值运算符为平凡的：
            // 1：它不是用户提供的（即它是隐式定义或预置的）；
            // 2：T 没有虚成员函数；
            // 3：T 没有虚基类；
            // 4：T 的每个直接基类选择的移动赋值运算符都是平凡的；
            // 5： T 的每个类类型（或类类型的数组）的非静态数据成员选择的移动赋值运算符都是平凡的；

            struct V {
                V &operator=(V &&other) {
                    // 这可能被调用一或两次
                    // 若调用两次，则 'other' 是刚被移动的 V 子对象
                    return *this;
                }
            };

            // 菱形继承，需要用 virtual 继承，这样 C 对象里就只会有一份 V 类的成员
//            struct A : virtual V {
//            }; // operator= 调用 V::operator=
//            struct B : virtual V {
//            }; // operator= 调用 V::operator=
//            struct C : B, A {
//            };      // operator= 调用 B::operator=，然后调用 A::operator=
//            // 但可能只调用一次 V::operator=
//
//            void test() {
//                C c1, c2;
//                c2 = std::move(c1);
//            }

            // 注：若一同提供了复制与移动赋值运算符，则当实参为右值（如无名临时量的纯右值，或如 std::move 的结果的亡值）时，重载决议选择移动赋值，
            // 当实参为左值（具名对象或返回左值引用的函数/运算符）时，选择复制赋值。
            // 若仅提供了复制赋值，则所有值类别时都选择它（只要它按值或按到 const 的引用接收其实参），这使得在移动不可用时，以复制赋值成为移动赋值的后备。
            struct A2 {
                std::string s;

                A2() : s("test") {}

                A2(const A2 &o) : s(o.s) { std::cout << "move failed!\n"; }

                A2(A2 &&o) : s(std::move(o.s)) {}

                A2 &operator=(const A2 &other) {
                    s = other.s;
                    std::cout << "copy assigned\n";
                    return *this;
                }

                A2 &operator=(A2 &&other) {
                    s = std::move(other.s);
                    std::cout << "move assigned\n";
                    return *this;
                }
            };

            A2 f(A2 a) { return a; }

            struct B2 : A2 {
                std::string s2;
                int n;
                // 隐式移动赋值运算符 B& B::operator=(B&&)
                // 调用 A 的移动赋值运算符
                // 调用 s2 的移动赋值运算符
                // 并进行 n 的逐位复制
            };

            struct C2 : B2 {
                ~C2() {} // 析构函数阻止隐式移动赋值
            };

            struct D2 : B2 {
                D2() {}

                ~D2() {} // 析构函数本会阻止隐式移动赋值
                D2 &operator=(D2 &&) = default; // 无论如何都强制移动赋值
            };

            void test2() {
                A2 a1, a2;
                std::cout << "Trying to move-assign A from rvalue temporary\n";
                a1 = f(A2()); // 从右值临时量移动赋值
                std::cout << "Trying to move-assign A from xvalue\n";
                a2 = std::move(a1); // 从亡值移动赋值

                std::cout << "Trying to move-assign B\n";
                B2 b1, b2;
                std::cout << "Before move, b1.s = \"" << b1.s << "\"\n";
                b2 = std::move(b1); // 调用隐式移动赋值
                std::cout << "After move, b1.s = \"" << b1.s << "\"\n";

                std::cout << "Trying to move-assign C\n";
                C2 c1, c2;
                c2 = std::move(c1); // 调用复制赋值运算符

                std::cout << "Trying to move-assign D\n";
                D2 d1, d2;
                d2 = std::move(d1);
            }
        }

        // virtual ~T();
        namespace destructor {
            // 声明说明符：friend、inline、virtual、constexpr、consteval (C++20 起) 或无（不允许返回类型）

            // 若下列任一条件为真，则类 T 的隐式声明或预置的析构函数不被定义 (C++11 前)被定义为弃置的 (C++11 起)：
            // 1：T 拥有无法销毁（拥有被弃置或不可访问的析构函数）的非静态数据成员
            // 2：T 拥有无法销毁（拥有被弃置或不可访问的析构函数）的直接或虚基类
            // 3：T 是联合体并拥有带非平凡析构函数的变体成员。
            // 4：隐式声明的析构函数为虚函数（因为基类有虚析构函数），对且解分配函数（operator delete()）的查找导致对有歧义、被弃置或不可访问函数的调用。

            // 当下列各项全部为真时，T 的析构函数为平凡的：
            // 1：析构函数不是用户提供的（表示它是隐式声明，或在其首个声明显示定义为预置的）
            // 2：析构函数非虚（即基类析构函数非虚）
            // 3：所有直接基类都拥有平凡析构函数
            // 4：所有类类型（或类的数组类型）的非静态数据成员都拥有平凡析构函数
            // 5：平凡析构函数是不进行任何动作的析构函数。有平凡析构函数的对象不要求 delete 表达式，并可以通过简单地解分配其存储进行释放。所有与 C 语言兼容的数据类型（POD 类型）都是可平凡析构的。

            class Base {
            public:
                virtual ~Base() {}
            };

            class Derived : public Base {
            };

            // 注：删除基类的指针会引发未定义行为，除非基类的析构函数为虚函数：
            void test() {
                Base *b = new Derived;
                delete b; // 安全
            };

            // 注：析构函数可以声明为纯虚，例如对于需要声明为抽象类，但没有其他可声明为纯虚的适合函数的基类。
            // 这种析构函数必须有定义，因为在销毁派生类时，所有基类析构函数都总是得到调用：
            class AbstractBase {
            public:
                virtual ~AbstractBase() = 0; // 纯虚函数
            };

            AbstractBase::~AbstractBase() {}

            class Derived2 : public AbstractBase {
            };

            void test2() {
                // AbstractBase obj;   // 编译错误，纯虚类，不能实例化
                Derived2 obj;           // OK
            }
        }

        namespace virtual_func {
            class base {
            public:
                virtual void virtual_func() {
                    std::cout << "base.virtual_func" << std::endl;
                }

                void func() {
                    std::cout << "base.func" << std::endl;
                }
            };

            class derived : public base {
            public:
                void virtual_func() {
                    std::cout << "derived.virtual_func" << std::endl;
                }

                void func() {
                    std::cout << "derived.func" << std::endl;
                }
            };

            void test() {
                base b;
                b.virtual_func(); // call base
                derived d;
                d.virtual_func(); // call derived

                b = d;
                b.virtual_func();   // call base

                base *pb = new derived;
                pb->virtual_func(); // call derived
            }
        }
    }
}