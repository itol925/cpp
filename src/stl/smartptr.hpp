#include <iostream>
#include <atomic>
#include <memory>
#include <thread>

namespace stl::smartPtr {
        namespace share_ptr_impl {
            // share_ptr 的简单实现
            class count {
            public:
                count(int s, int w) {
                    share_count = s;
                    weak_count = w;
                }

                std::atomic<int> share_count{0};
                std::atomic<int> weak_count{0};
            };

            template<typename T>
            class my_share_ptr {
            public:
                explicit my_share_ptr(T *t = nullptr) {
                    this->t = t;
                    this->c = new count(1, 0);
                }

                my_share_ptr(const my_share_ptr<T> &other) {
                    t = other.t;
                    c = other.c;
                    ++c->share_count;
                }

                ~my_share_ptr() {
                    release();
                }

                my_share_ptr<T> &operator=(const my_share_ptr<T> &other) {
                    if (&other == this) {
                        return *this;
                    }
                    // 为啥要先 release()，因为 this 可能之前有指向其他的 T 对象，这里需要释放掉之前的对象
                    release();
                    t = other.t;
                    c = other.c;
                    ++c->share_count;
                    return *this;
                }

                T *get() {
                    return t;
                }

                int use_count() {
                    return c->share_count;
                }

            private:
                void release() {
                    --c->share_count;
                    if (c->share_count <= 0) {
                        delete t;
                        delete c;
                    }
                }

            private:
                T *t;
                count *c{};
            };

            void test() {
                auto p_int = smartPtr::share_ptr_impl::my_share_ptr<int>(new int(3));
                std::cout << "use:" << p_int.use_count() << std::endl;
                auto p_int2 = p_int;
                std::cout << "use:" << p_int.use_count() << std::endl;

                std::cout << "val:" << *p_int2.get() << std::endl;
            }
        }

        namespace share_ptr_demo {
            // share_ptr 不完全线程完全，但是控制字段是线程安全的，比如 引用计数
            void test(){
                auto int_p = std::make_shared<int>(0);
                std::thread t1([&int_p]{
                    for (int i = 0; i < 1000; i++) {
                        *int_p = *int_p + 1;
                    }
                });
                std::thread t2([&int_p]{
                    for (int i = 0; i < 1000; i++) {
                        *int_p = *int_p + 1;
                    }
                });
                t1.join();
                t2.join();
                std::cout << "int_p:" << *int_p << std::endl;

                char* text = "hello world";
                auto sbb_ptr = std::make_shared<std::string>(text);
                char* s = const_cast<char *>(sbb_ptr->c_str());
            }
            void test2() {
                //std::atomic<std::shared_ptr<long>> instance;
                std::cout << "test2" << std::endl;
            }
            void test3() {
                std::cout << "test3" << std::endl;
                int a = 10;
                auto p = std::make_shared<int>(a);
                std::cout << "use_count:" << p.use_count() << std::endl;
            }
        }

        namespace weak_ptr_demo {
            // weak_ptr 可以用来弱引用对象。比如我想要获取某个 share_ptr 的引用，但是不想让它增加引用计数，那么可以转为 weak_ptr 来使用
            void show_val(std::weak_ptr<int> v) {
                if (auto i = v.lock()) {
                    std::cout << "val is " << *i << std::endl;
                } else {
                    std::cout << "val is release" << std::endl;
                }
            }

            void test() {
                auto share_i = std::make_shared<int>(10);
                std::cout << "create share_i:" << *share_i << std::endl;
                auto weak_i = std::weak_ptr<int>(share_i);
                show_val(weak_i);

                share_i.reset();
                std::cout << "reset share_i" << std::endl;

                show_val(weak_i);
            }
        }

        namespace unique_ptr_demo {
            void foo(std::unique_ptr<int> unique_i) {
                std::cout << "val:" << *unique_i << std::endl;
            }

            void test() {
                auto unique_i = std::make_unique<int>(10);

                //foo(unique_i); error! unique_ptr 不能复制
                foo(std::move(unique_i));

                // exception! 下面是不确定调用。因为unique_i 对象已经被转移了
                std::cout << "val is:" << *unique_i << std::endl;
            }
        }
    }