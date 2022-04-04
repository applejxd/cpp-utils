//
// Created by applejxd on 2021/11/01.
//

#include "gtest/gtest.h"
#include <string>
#include <utility>
#include <vector>
#include <climits>

#include "util/config.h"
#include "util/file_io.h"

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

    TEST(CsvTest, WriteReadCheck) {
        const vector<vector<double>> table{{4,   2},
                                           {23,  5},
                                           {132, 2}};
        util::WriteCsv<double>("data/table.csv", table);

        vector<vector<string>> read_table;
        util::ReadCsv("data/table.csv", &read_table, nullptr);

        EXPECT_EQ(stoi(read_table[0][0]), 4);
        EXPECT_EQ(stoi(read_table[0][1]), 2);
    }

    TEST(VarTest, WriteReadCheck) {
        typedef struct TestStruct_ {
            int int_var_;
            string string_var_;

            TestStruct_(): int_var_(INT_MAX) {}
            explicit TestStruct_(string string_var) : int_var_(42),
                                                      string_var_(std::move(string_var)) {}
        } TestStruct;

        TestStruct var("Invisible Pink Unicorn");
        util::SaveVar<TestStruct>("data/var.dat", var);

        TestStruct read_var;
        util::LoadVar<TestStruct>("data/var.dat", &read_var);

        EXPECT_EQ(read_var.int_var_, 42);
        EXPECT_EQ(read_var.string_var_, "Invisible Pink Unicorn");
    }

//    TEST(SerializationTest, WriteReadCheck) {
//        typedef struct TestStruct_ {
//            int int_var_;
//            string string_var_;
//
//            TestStruct_(): int_var_(INT_MAX) {}
//            explicit TestStruct_(string string_var) : int_var_(42),
//                                                      string_var_(std::move(string_var)) {}
//        } TestStruct;
//
//        TestStruct var("Invisible Pink Unicorn");
//        util::SaveSerializedData<TestStruct>("data/serial.dat", var);
//
//        TestStruct read_var = util::LoadSerializedData<TestStruct>("data/serial.dat");
//
//        EXPECT_EQ(read_var.int_var_, 42);
//        EXPECT_EQ(read_var.string_var_, "Invisible Pink Unicorn");
//    }
}


