#include <iostream>

namespace stl {
    namespace template_demo {
        namespace concept_demo {
            // since c++ 20
            // 概念。用于指定模板参数必须满足的约束条件，即可以用来定义语义！！！

            // demo1
            // 通过 concept 关键字定义了 Hashable 这个概念，Hashable 要求 T 的对象必须满足能够被转换成 size_t 对象
            template<typename T>
            concept Hashable = std::is_convertible_v<T, std::size_t>;

            //concept Hashable = requires(T a) {
            //    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
            //};
            template<Hashable T>
            // 1：形式一
            std::size_t hashtable1(T a) {
                return static_cast<std::size_t>(a);
            }

            template<typename T>
            // 2：形式2
            std::size_t hashtable2(T a) requires Hashable<T> {
                return static_cast<std::size_t>(a);
            }

            void test_hashable() {
                hashtable1(12);   // OK
                hashtable2(21.0); // OK
                //func("abc");// Error.
            }

            // demo2
            // 定义一个只能是整数类型的concept，整数类型包括 char, unsigned char, short, ushort, int, unsinged int, long等。
            template<typename T>
            concept Integral = std::is_integral_v<T>;

            template<Integral T>
            T integral_add(T t1, T t2) {
                return t1 + t2;
            }

            void test_integral() {
                int a = integral_add(1, 2);
                std::cout << "integral_add:" << a << std::endl;
            }

            // demo3
            class Base {
            };

            template<class T, class U>
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
                { a % 2 == 0 } -> std::same_as<bool>;
            };

            template<EvenNumber T>
            void test_even_number(T t) {
                std::cout << "t is even number" << std::endl;
            }

            void test() {
                test_integral();
                test_hashable();
                test_even_number(2);
                test_even_number(1);
                //double d = add(1.0, 2.0); error! 1.0 不是整数
            }

            // 推断出返回值的类型
            template<typename T, typename U>
            auto add(T t, U u) -> decltype(t + u) {
                return t + u;
            }

            // trait
            class dog {
            };

            class flower {
            };

            /**
             * 定义 区分 animal 的 trait
             * 对所有预期的输出指定是否为 animal
             * 这么做的好处是：1 编译器确定；2 将 is_animal 判断隔离到了 DescribeAnyThing 外面
             * */
            template<typename T>
            struct obj_traits {
                static const bool is_animal = false;
            };
            template<>
            struct obj_traits<dog> {
                static const bool is_animal = true;
            };
            template<>
            struct obj_traits<flower> {
                static const bool is_animal = false;
            };

            /** case1:
             * DescribeAnyThing 要求
             * 如果 T 是 animal 则输出 animal，否则输出非 animal
             */
            template<typename T>
            class DescribeAnyThing {
            public:
                void desc(T sth) {
                    if (obj_traits<T>::is_animal) {
                        std::cout << "this is animal" << std::endl;
                    } else {
                        std::cout << "this is not animal" << std::endl;
                    }
                }
            };
        }

        template<typename T>
        void addOne(T& t) {
            t++;
        }

        template<typename T, int dim>
        class MyArr {
        public:
            MyArr() {
                for (int i = 0; i < dim; i++) {
                    arr[i] = i * 2;
                }
            }
            void print() {
                std::cout << "arr:";
                for (int i = 0; i < dim; i++) {
                    std::cout << arr[i] << " ";
                }
                std::cout << std::endl;
            }
        private:
            T arr[dim];
        };

        void test() {
            int i = 0;
            addOne(i);
            std::cout << "i=" << i << std::endl;

            MyArr<int, 3> arr;
            arr.print();
        }
    }
}