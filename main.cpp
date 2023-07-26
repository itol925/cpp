#include "src/stl/initialization.hpp"
#include "src/stl/function.hpp"
#include "src/stl/coroutine.hpp"

#include "src/boost/io.hpp"
#include "src/continuable/continuable.hpp"

int main(int argc, char** argv) {
    //stl::init::init();
    //stl::func::test_func();
    stl::test_coroutine();

    //boost_demo::test_io();
    //continue_demo::test();
}