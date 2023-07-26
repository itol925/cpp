#include <iostream>

namespace stl {
    namespace template_demo {
        namespace concept_demo {
            // since c++ 20
            // 概念。用于指定模板参数必须满足的约束条件，即可以用来定义语义！

            // 如下面的例子：
            // 通过 concept 关键字定义了 Hashable 这个概念，Hashable 要求 T 的对象必须满足能够被转换成 size_t 对象
            template<typename T>
            concept Hashable = requires(T a) {
                { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
            };

            // 使用
            template<Hashable T>
            std::size_t func(T a) {
                return static_cast<std::size_t>(a);
            }

            void test_concept() {
                func(12);   // OK
                func(21.0); // OK
                //func("abc");// Error.
            }

            // 其它例子
            // 1：定义数字的概念
            template<typename T>
            concept Integral =  std::is_integral<T>::value;
            // 2：定义继承关系
            class Base {};
            template <class T, class U>
            concept Derived = std::is_base_of<U, T>::value;
            template<Derived<Base> T>
            void derived_func(T);  // T 由 Derived<T, Base> 约束
            // 3：多个约束条件
            template<typename T>
            concept SignedIntegral = Integral<T> && std::is_signed<T>::value;
            template<typename T>
            concept UnsignedIntegral = Integral<T> && !SignedIntegral<T>;
        }
    }
}