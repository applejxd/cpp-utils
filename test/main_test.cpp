//
// Created by applejxd on 2021/11/01.
//

#include "gtest/gtest.h"
#include <string>

#include "../config.h"

namespace {
    TEST(BasicTest, IntCheck) {
        int test = 1;
        EXPECT_EQ(test, 1);
    }

    TEST(ConfigTest, IntCheck){
        auto test = util::GetParam<int>("group.key_int");
        EXPECT_EQ(test, 42);
    }

    TEST(ConfigTest, StringCheck){
        auto test = util::GetParam<std::string>("group.key_string");
        EXPECT_EQ(test, "Test");
    }
}


