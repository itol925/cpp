//#include <iostream>
//#include <coroutine>
//#include <queue>
//
//namespace stl {
//    using suspend_always = std::suspend_always;
//    using suspend_never = std::suspend_never;
//    using std::coroutine_handle;
//
//    namespace coroutine {
//        namespace readme {
//            // 协程就是用户态线程内可以被异步执行的函数。用来在用户态下解决异步问题。
//
//            // *目前在C/C++中比较知名的协程(类协程)库有
//            // Boost.Fiber
//            // Boost.Coroutine
//            // fiber
//            // libco
//            // libtask
//
//            // *协程根据实现方式不同，分为有栈协程(stackful coroutine)和无栈协程(stackless coroutine)。
//            // 有栈协程可通过操作系统提供的系统调用实现;
//            // 无栈协程需要语言标准和编译器支持。
//
//            // *微软拟提的C++20标准中(目前是ts,即:<experimental/coroutine>)的协程属于stackless coroutine。
//
//            // *协程函数特点：
//            // 1：首次调用协程函数，会从堆中分配一个协程上下文，调用方的返回地址、入口函数、交出控制权等信息保存在协程上下文中。
//            // 2：当协程中途交出控制权后，协程上下文不会被删除(相当于函数退出之后，上下文环境还被保存，类比线程切换)。
//            // 3：当协程再次获得控制权后，会自动从协程上下文中恢复调用环境，然后从上一次交出控制权的下一条语句继续执行(加载目标协程环境，类比线程切换)。
//            // 4：协程函数返回(非中途交出控制权)后，协程上下文将被删除。
//            // 5：若再次调用协程函数，视为首次调用。
//
//            // *有栈协程(Stackful Coroutines)特点：
//            // 1：每个协程都有一个预先分配的调用栈(Call Stack)。
//            // 2：每个协程都属于且仅属于创建它的线程。
//            // 3：一个线程可以包含多个协程。
//            // 4：线程本身也可以是一个协程，成为主协程(Primary Coroutine)。
//            // 5：协程必须主动交出控制权，否则同一线程的其它协程均无法获得执行机会。
//            // 6：协程执行路径上，任何被调用的函数均可在任何位置交出控制权。
//            // 7：如果允许协程把控制权交给同一线程的其它协程，则称为对称协程(Symmetry Coroutines)。如果只允许协程把控制权交给主协程，主协程作为调度器，负责分配执行权，则称为非对称协程(Asymmetry Coroutines)。
//            // 8：属于同一线程的多个协程之间没有数据争用(Data Race)问题。
//            // 9：无需修改语言标准和编译器，利用系统调用即可实现。
//
//            // *无栈协程(Stackless Coroutines)特点：
//            // 1：每个协程的执行环境，仅需包含调用栈(Call Stack)的顶层栈帧(Top Call Stack Frame)，而非整个调用栈，因而空间开销极小。
//            // 2：协程执行路径上，只有特定语句才能交出控制权。
//            // 3：无需协程调度器。
//            // 4：调用协程函数时，同一协程函数的不同部分，有可能在不同的线程环境中执行。因此需要处理好数据争用(Data Race)问题。这个问题实际是线程间数据争用问题。
//            // 5：需要语言标准和编译器支持。
//
//            // *怎么识别C++20中的协程
//            // 函数体内包含co_await、co_yield、co_return中任何一个关键字，即认为函数是协程函数。其中：
//            // 1：co_await：挂起（or不挂起）协程。
//            // 2：co_return：返回结果并结束协程。
//            // 3：co_yield：返回结果并挂起协程。
//
//            // *协程的概念模型
//            // ** Awaitable
//            // 通过 co_await 操作符触发 Awaitable 对象的动作，实现协程函数的转移、恢复控制权。Awaitable动作包括：
//            // 1：await_ready：返回Awaitable实例是否已经ready。协程开始会调用此函数，如果返回true，表示你想得到的结果已经得到了，协程不需要执行了。所以大部分情况这个函数的实现是要return false。
//            // 2：await_suspend：挂起awaitable。该函数会传入一个coroutine_handle类型的参数。这是一个由编译器生成的变量。在此函数中调用handle.resume()，就可以恢复协程。
//            // 3：await_resume：当协程重新运行时，会调用该函数。这个函数的返回值就是co_await运算符的返回值。
//
//            // ** Promise & Future
//            // *** Promise
//            // Promise 对象保存了协程的状态信息，包括局部变量，用户数据等。一个Promise对象需要实现如下方法：
//            // 1：initial_suspend: 返回一个 Awaitable 对象
//            // 2：final_suspend: 返回一个 Awaitable 对象
//            // 3：get_return_object: 返回一个 Future 对象给 Caller
//            // 4：unhandled_exception: 处理异常
//            // 5：return_value/return_void: co_return 时返回值给 Caller
//            // 6：yield_value: 挂起时返回值给 Caller
//            // *** Future
//            // 协程函数启动时，会返回一个 Future 对象给 Caller，Caller 通过 Future 对象来控制协程的执行。
//            // Future 通常会包含 Promise 的 handle，Caller 通过此 handle 来调用 Promise。Future 开放给 Caller 控制方法有：
//            // 1：destroy: 销毁 Promise 对象
//            // 2：from_promise: 静态方法，从 Promise 对象返回其 coroutine_handle 句柄
//            // 3：done: 是否处于 final_suspend 阶段
//            // 4：promise: 返回 Promise 对象引用
//            // 5：resume/operator(): 恢复到协程
//
//            // ref:
//            // https://zhuanlan.zhihu.com/p/218156339
//        }
//
//        namespace demo1 {
//            template<typename T>
//            struct Future {
//                struct promise_type {
//                    promise_type() { std::cout << "promise_type created\n"; }
//
//                    ~promise_type() { std::cout << "promise_type died\n"; }
//
//                    auto get_return_object() { //get return object
//                        std::cout << "get_return_object called\n";
//                        // pass handle to create "return object"
//                        return Future<T>{coroutine_handle<promise_type>::from_promise(*this)};
//                    }
//
//                    auto initial_suspend() { // called before run coroutine body
//                        std::cout << "initial_suspend is called\n";
//                        // return suspend_never{}; // dont suspend it
//                        return suspend_always{};
//                    }
//
//                    auto return_void() { // called when just before final_suspend, conflict with return_value
//                        std::cout << "return_void is called\n";
//                        return suspend_never{}; // dont suspend it
//                        //return suspend_always{};
//                    }
//
//                    auto yield_value(int t) { // called by co_yield()
//                        std::cout << "yield_value called\n";
//                        value = t;
//                        return suspend_always{};
//                    }
//
//                    auto final_suspend() noexcept { // called at the end of coroutine body
//                        std::cout << "final_suspend is called\n";
//                        return suspend_always{};
//                    }
//
//                    void unhandled_exception() { //exception handler
//                        std::exit(1);
//                    }
//
//                    T value;
//                };
//
//                T get() {
//                    std::cout << "# Got return value\n";
//                    if (!(this->handle.done())) {
//                        handle.resume();
//                        return handle.promise().value;
//                    }
//                    return T{};
//                }
//
//                coroutine_handle<promise_type> handle;
//            };
//
//            struct AwaiableObj {
//                int a = 0;
//
//                bool await_ready() {
//                    std::cout << "await_ready called\n";
//                    return true;
//                }
//
//                auto await_suspend(coroutine_handle<> awaiting_handle) {
//                    std::cout << "await_suspend called\n";
//                    // return;
//                    // return true;
//                    return false;
//                    // return awaiting_handle;
//                }
//
//                auto await_resume() {
//                    std::cout << "await_resume called\n";
//                    return a++;
//                }
//            };
//
//            Future<int> await_routine() {
//                auto a = AwaiableObj{};
//                for (int i = 0; i < 5; i++) {
//                    auto v = co_await a;
//                    co_yield v;
//                }
//            }
//
//            void test_demo1() {
//                std::cout << "-- demo1 --" << std::endl;
//                auto a = await_routine();
//                auto b = a.get();
//
//                std::cout << "value is " << b << std::endl;
//                b = a.get();
//                std::cout << "value is " << b << std::endl;
//                b = a.get();
//                std::cout << "value is " << b << std::endl;
//                b = a.get();
//                std::cout << "value is " << b << std::endl;
//                b = a.get();
//                std::cout << "value is " << b << std::endl;
//                std::cout << "end";
//            }
//        }
//
//        namespace demo2 {
//            struct Future {
//                struct promise_type {
//                    suspend_never initial_suspend() { return {}; }
//
//                    suspend_never final_suspend() noexcept { return {}; }
//
//                    suspend_always yield_value(int v) {
//                        std::cout << "coroutine task: call yield_value " << v << std::endl;
//                        return {};
//                    }
//
//                    void return_value(int r) {
//                        std::cout << "coroutine task: call return_value " << r << std::endl;
//                    }
//
//                    Future get_return_object() {
//                        return {coroutine_handle<promise_type>::from_promise(*this)};
//                    }
//
//                    void unhandled_exception() {}
//                };
//
//                coroutine_handle<promise_type> handle;
//            };
//
//            struct AwaiableObj {
//                bool await_ready() {
//                    std::cout << "coroutine: call await_ready" << std::endl;
//                    return false;
//                }
//
//                void await_suspend(coroutine_handle<> awaiting_handle) {
//                    std::cout << "coroutine: call await_suspend" << std::endl;
//                }
//
//                int await_resume() {
//                    std::cout << "coroutine: call await_resume" << std::endl;
//                    return 11;
//                }
//            };
//
//            Future coroutine_func() {
//                std::cout << "coroutine:call co_await" << std::endl;
//                int val = co_await AwaiableObj();
//                std::cout << "coroutine:call co_yield " << val << std::endl;
//                co_yield 66;
//                // co_await promise.yield_value()
//
//                std::cout << "coroutine:call co_return " << val << std::endl;
//                co_return 88;
//                // co_await promise.final_suspend();
//            }
//
//            void test_demo2() {
//                std::cout << "main:call coroutine_func" << std::endl;
//                Future c = coroutine_func();
//                std::cout << "main:call resume" << std::endl;
//                c.handle.resume();
//                std::cout << "main:call resume2" << std::endl;
//                c.handle.resume();
//            }
//        }
//
//        namespace demo3 {
//            std::queue<int> queue;
//
//            struct Task {
//                struct promise_type {
//                    suspend_never initial_suspend() { return {}; }
//
//                    suspend_never final_suspend() noexcept { return {}; }
//
//                    suspend_always yield_value(int v) {
//                        queue.push(v);
//                        return {};
//                    }
//
//                    Task get_return_object() {
//                        return {coroutine_handle<promise_type>::from_promise(*this)};
//                    }
//
//                    void unhandled_exception() {}
//
//                    void return_void() {}
//                };
//
//                coroutine_handle<promise_type> handle;
//            };
//
//            struct Producer {
//                bool await_ready() { return false; }
//
//                void await_suspend(coroutine_handle<> awaiting_handle) {}
//
//                void await_resume() {}
//            };
//
//            Task produce() {
//                co_await Producer();
//                for (int i = 0; i < 10; ++i) {
//                    co_yield i;
//                }
//                co_return;
//            }
//
//            void consume() {
//                auto p = produce();
//                p.handle.resume();
//                while (!queue.empty()) {
//                    int v = queue.front();
//                    queue.pop();
//                    std::cout << "consumed val:" << v << std::endl;
//                    p.handle.resume();
//                }
//            }
//
//            void test_demo3() {
//                consume();
//            }
//        }
//
//        namespace demo4 {
//            struct CoRet {
//                struct promise_type {
//                    int _out;
//                    int _res;
//
//                    suspend_never initial_suspend() { return {}; }
//
//                    suspend_always final_suspend() noexcept { return {}; }
//
//                    void unhandled_exception() {}
//
//                    CoRet get_return_object() {
//                        return {coroutine_handle<promise_type>::from_promise(*this)};
//                    }
//
//                    suspend_always yield_value(int r) {
//                        _out = r;
//                        return {};
//                    }
//
//                    void return_value(int r) {
//                        _res = r;
//                    }
//                };
//
//                coroutine_handle<promise_type> _h; // _h.resume(), _h()
//            };
//            struct Note {
//                int guess;
//            };
//
//            struct Input {
//                Note &_in;
//
//                bool await_ready() { return false; }
//
//                void await_suspend(coroutine_handle<CoRet::promise_type> h) {}
//
//                int await_resume() { return _in.guess; }
//            };
//
//            CoRet Guess(Note &note) {
//                // CoRet::promise_type promise;
//                // CoRet ret = promise.get_return_object();
//                // co_await promise.initial_suspend();
//                int res = (rand() % 30) + 1;
//                Input input{note};
//                int g = co_await input;
//                std::cout << "coroutine: You guess " << g << std::endl;
//
//                co_yield (res > g ? 1 : (res == g ? 0 : -1));
//                // co_await promise.yield_value()
//
//                co_return res;
//                // co_await promise.final_suspend();
//            }
//
//            void test_demo4() {
//                srand(time(nullptr));
//                Note note;
//                auto ret = Guess(note);
//                std::cout << "main: make a guess ..." << std::endl;
//                note.guess = 10;
//                ret._h.resume(); // resume from co_await
//                std::cout << "main: result is " <<
//                          ((ret._h.promise()._out == 1) ? "larger" :
//                           ((ret._h.promise()._out == 0) ? "the same" : "smaller"))
//                          << std::endl;
//
//                ret._h.resume(); // resume from co_yield
//                if (ret._h.done()) {
//                    std::cout << "main: the result is " << ret._h.promise()._res << std::endl;
//                }
//            }
//        }
//    }
//
//    void test_coroutine() {
//        std::cout << "-- test coroutine --" << std::endl;
//        //coroutine::demo1::test_demo1();
//        //coroutine::demo2::test_demo2();
//        //coroutine::demo3::test_demo3();
//        coroutine::demo4::test_demo4();
//    }
//}