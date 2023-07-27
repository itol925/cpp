#include <iostream>

namespace stl {
    namespace template_demo {
        namespace concept_demo {
            // since c++ 20
            // 概念。用于指定模板参数必须满足的约束条件，即可以用来定义语义！！！

            // demo1
            // 通过 concept 关键字定义了 Hashable 这个概念，Hashable 要求 T 的对象必须满足能够被转换成 size_t 对象
            template<typename T>
            concept Hashable = requires(T a) {
                { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
            };
            // 用概念来约束 template
            // 1：形式一
            template<Hashable T>
            std::size_t func(T a) {
                return static_cast<std::size_t>(a);
            }
            // 2：形式2
            template<typename T>
            std::size_t func2(T a) requires Hashable<T> {
                return static_cast<std::size_t>(a);
            }
            // use template
            void test_hashable() {
                func(12);   // OK
                func(21.0); // OK
                //func("abc");// Error.
            }

            // demo2
            // 定义概念
            template<typename T>
            //concept Integral = std::is_integral<T>::value;
            concept Integral = requires (T a) {
                std::is_integral<T>(a);
            };
            // 应用概念到 template 上。形式1
            template<Integral T>
            void func_int(T t) {}
            // 应用概念 形式2
            template<typename T>
            void func_int2(T t) requires Integral<T> {}

            // demo3
            class Base {};
            template <class T, class U>
            concept Derived = std::is_base_of<U, T>::value;
            template<Derived<Base> T>
            void func_derived(T);
            template<typename T, typename U>
            void func_derived2(T) requires Derived<U, T>;

            // 多个约束条件
            template<typename T>
            concept SignedIntegral = Integral<T> && std::is_signed<T>::value;
            template<typename T>
            concept UnsignedIntegral = Integral<T> && !SignedIntegral<T>;

            // 定义偶数
            template<typename T>
            concept EvenNumber = requires(T a) {
                std::is_integral(a) && a % 2 == 0;
            };
        }
    }
}