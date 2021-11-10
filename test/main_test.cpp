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

    TEST(ConfigTest, IntCheck) {
        auto test = util::GetParam<int>("group.key_int");
        EXPECT_EQ(test, 42);
    }

    TEST(ConfigTest, StringCheck) {
        auto test = util::GetParam<string>("group.key_string");
        EXPECT_EQ(test, "Test");
    }

    TEST(CsvTest, LineCheck) {
        const vector<vector<double>> table{{4,   2},
                                           {23,  5},
                                           {132, 2}};
        util::WriteCsv<double>("data/table.csv", table);

        vector<vector<string>> read_table;
        util::ReadCsv("data/table.csv", &read_table, nullptr);

        EXPECT_EQ(stoi(read_table[0][0]), 4);
        EXPECT_EQ(stoi(read_table[0][1]), 2);
    }
}


