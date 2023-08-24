#include "src/boost/io.hpp"
#include "src/boost/continuable.hpp"

#include "src/stl/initialization.hpp"
#include "src/stl/function.hpp"
#include "src/stl/coroutine.hpp"
#include "src/stl/overload.hpp"
#include "src/demo/cs/test.hpp"
#include "src/stl/smartptr.hpp"
#include "src/stl/chrono.hpp"
#include "src/stl/ref.hpp"
#include "src/stl/template.hpp"
#include "src/stl/tools.hpp"
#include "src/stl/classes.hpp"
#include "src/leetcode/test1.hpp"
#include "src/leetcode/sort.hpp"
#include "src/boost/threadPool.hpp"

int main(int argc, char** argv) {
    //boost_demo::test_io();
    //continue_demo::test();

    //stl::init::init();
    //stl::func::test();
    //stl::test_coroutine();

    //stl::overload_demo::test();

    //demo::cs::test();
    //stl::smartPtr::share_ptr_impl::test();
    //stl::smartPtr::weak_ptr_demo::test();

    //stl::smartPtr::unique_ptr_demo::test();
    //stl::smartPtr::share_ptr_demo::test();
    //stl::chrono_demo::test();

    //stl::ref_demo::test();

    //stl::template_demo::concept_demo::test();

    //stl::tools::test();
    //stl::classes::virtual_func::test();
    //leetcode::test();
    leetcode::sort::test();
    //thread_demo::test();
}