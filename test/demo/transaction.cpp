//
// Created by Yinglong Pan on 2024/11/21.
//
#include "gtest/gtest.h"
#include "transaction.hpp"

using namespace demo::trans;
TEST(Transaction, Test) {
    Transaction<int> trans("type", "name", cb1);
    Transaction trans2 = std::move(trans);
    trans2.done(3);

    Transaction trans3("type1", "name1");
    Transaction trans4 = std::move(trans3);
    trans4.done();
    //Transaction<int> trans3 = trans2;
}