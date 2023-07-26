#include "src/base/initialization.hpp"
#include "src/base/function.hpp"
#include "src/base/coroutine.hpp"

#include "src/boost/io.hpp"


int main(int argc, char** argv) {
    //base::init::init();
    //base::func::test_func();
    //base::test_coroutine();

    boost_demo::test_io();
}