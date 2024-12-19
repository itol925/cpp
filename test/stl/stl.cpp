//
// Created by Yinglong Pan on 2024/11/21.
//
#include "gtest/gtest.h"
#include <csignal>
#include "stl/initialization.hpp"
#include "stl/function.hpp"
#include "stl/coroutine.hpp"
#include "stl/overload.hpp"
#include "stl/smartptr.hpp"
#include "stl/chrono.hpp"
#include "stl/ref.hpp"
#include "stl/template.hpp"
#include "stl/tools.hpp"
#include "stl/classes.hpp"
#include "stl/ptr.hpp"
#include "stl/condition.hpp"
#include "stl/promise.hpp"
#include "stl/member.hpp"
#include "stl/exceptions.hpp"
#include "stl/noncopyable.hpp"
#include "stl/segment.hpp"
#include "stl/storage.hpp"
#include "stl/error.hpp"

using namespace stl;
TEST(STL, Init) {
    stl::init::init_test();
}

TEST(STL, Function) {
    stl::func::func_ptr::test();
    stl::func::lambda_demo::test();
    stl::func::function_bind::test();
    stl::func::function_template::test();
}

TEST(STL, Overload) {
    stl::overload_demo::test_user_define_conversion();
}

TEST(STL, SmartPoint) {
    stl::smartPtr::share_ptr_impl::test();
    stl::smartPtr::share_ptr_demo::test();
    stl::smartPtr::weak_ptr_demo::test();

    std::signal(SIGSEGV, [](int signal)->void {
        std::cout << "Caught signal: " << signal << std::endl;
        EXPECT_EQ(signal, SIGSEGV);
        std::exit(signal);
    });
    stl::smartPtr::unique_ptr_demo::test(); // 此句预期会报错
}

TEST(STL, Chrono) {
    stl::chrono_demo::test();
}

TEST(STL, Ref) {
    stl::ref_demo::test_left_ref();
    stl::ref_demo::test_right_ref();
    stl::ref_demo::test_reference_wrapper();
    stl::ref_demo::test_left_expression();
    stl::ref_demo::test_forward();
    stl::ref_demo::test_virtual();
}

TEST(STL, Templete) {
    stl::template_demo::concept_demo::test();
    stl::template_demo::test();
}

TEST(STL, Tools) {
    stl::tools::test();
}

TEST(STL, Cls) {
    stl::classes::member_func::test_rvalue();
    stl::classes::default_constructor::test();
    stl::classes::copy_constructor::test();
    stl::classes::move_constructor::test();
    stl::classes::copy_operator::test();
    stl::classes::move_operator::test();
    stl::classes::destructor::test();
    stl::classes::virtual_func::test();
    stl::classes::test_non_copy();
}

TEST(STL, Ptr) {
    stl::ptr::test();
}

TEST(STL, Condition) {
    stl::condition_demo::test();
}

TEST(STL, Promise) {
    stl::promise_demo::test();
}

TEST(STL, Members) {
    stl::members::test();
}

TEST(STL, Exeception) {
    stl::exception_demo::test();
}

TEST(STL, Segment) {
    stl::segment::test();
}