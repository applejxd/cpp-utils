//
// Created by myama on 2021/11/01.
//

#ifndef CSV_IO_H
#define CSV_IO_H

#include <vector>
#include <string>
#include <stdexcept>

namespace util {
    using std::vector;
    using std::string;

    inline vector<vector<string>> ReadCsv(const string &file_name, bool skip_header=false) {
        std::ifstream ifs(file_name);
        if (!ifs) {
            throw std::runtime_error("Cannot open csv file: " + file_name);
        }

        vector<string> lines{};
        {
            string str_buf;
            // ヘッダ行読み飛ばし
            if (skip_header) { getline(ifs, str_buf); }
            // ペイロード読み込み
            while (getline(ifs, str_buf)) {
                lines.push_back(str_buf);
            }
        }

        vector<vector<string>> table{};
        {
            for (const auto &line : lines) {
                vector<string> words{};
                {
                    std::istringstream ss(line);
                    string word;
                    while (std::getline(ss, word, ',')) {
                        words.push_back(word);
                    }
                }
                table.push_back(words);
            }
        }

        return table;
    }

    template<typename T>
    inline void WriteCsv(const string &file_name, const vector<vector<T>> &table, const string &header = {}) {
        std::ofstream ofs(file_name);

        if (!header.empty()) {
            ofs << header << std::endl;
        }

        for (const auto &line: table) {
            for (unsigned int idx = 0; idx < line.size(); ++idx) {
                ofs << line[idx];
                if (idx != line.size() - 1) {
                    ofs << ",";
                }
            }
            ofs << std::endl;
        }
    }
}

#endif //CSV_IO_H
