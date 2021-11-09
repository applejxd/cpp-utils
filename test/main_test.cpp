//
// Created by applejxd on 2021/11/01.
//

#include "gtest/gtest.h"
#include <string>
#include <vector>

#include "../config.h"
#include "../csv.h"

namespace {
    using std::string;
    using std::vector;

    TEST(BasicTest, IntCheck) {
        int test = 1;
        EXPECT_EQ(test, 1);
    }

    TEST(ConfigTest, IntCheck){
        auto test = util::GetParam<int>("group.key_int");
        EXPECT_EQ(test, 42);
    }

    TEST(ConfigTest, StringCheck){
        auto test = util::GetParam<string>("group.key_string");
        EXPECT_EQ(test, "Test");
    }

    TEST(CsvTest, LineCheck){
        vector<vector<string>> table = util::ReadCsv("data/rand.csv", true);

        EXPECT_EQ(stoi(table[0][0]), 28);
        EXPECT_EQ(stoi(table[0][1]), 75);
    }
}


