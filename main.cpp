#include "src/boost/io.hpp"
#include "src/continuable/continuable.hpp"

#include "src/stl/initialization.hpp"
#include "src/stl/function.hpp"
#include "src/stl/coroutine.hpp"
#include "src/stl/overload.hpp"
#include "src/demo/cs/test.hpp"
#include "src/stl/smartptr.hpp"
#include "src/stl/chrono.hpp"

int main(int argc, char** argv) {
    //boost_demo::test_io();
    //continue_demo::test();

    //stl::init::init();
    //stl::func::test_func();
    //stl::test_coroutine();

    //stl::overload_demo::test();

    //demo::cs::test();
    //stl::smartPtr::share_ptr_impl::test();
    //stl::smartPtr::weak_ptr_demo::test();

    //stl::smartPtr::unique_ptr_demo::test();
    //stl::smartPtr::share_ptr_demo::test();
    stl::chrono_demo::test();
}