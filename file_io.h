//
// Created by myama on 2021/11/01.
//

#ifndef CSV_IO_H
#define CSV_IO_H

#include <vector>
#include <string>
#include <stdexcept>
#include <glog/logging.h>

namespace util {
    using std::vector;
    using std::string;

    inline void ReadCsv(const string &file_name, vector<vector<string>> *table, vector<string> *header) {
        if (table == nullptr) {
            LOG(FATAL) << "Payload table is null pointer.";
        }
        table->clear();

        std::ifstream ifs(file_name);
        if (!ifs) {
            LOG(FATAL) << "Cannot open csv file: " << file_name;
        } else {
            LOG(INFO) << "Read: " << file_name;
        }

        // 行読み込み
        vector<string> lines{};
        {
            string str_buf;
            // ペイロード読み込み
            while (getline(ifs, str_buf)) {
                lines.push_back(str_buf);
            }
        }

        // セル読み込み
        for (const auto &line : lines) {
            vector<string> words{};
            {
                std::istringstream ss(line);
                string word;
                while (std::getline(ss, word, ',')) {
                    words.push_back(word);
                }
            }
            table->push_back(words);
        }

        if (header != nullptr) {
            std::copy(table->begin()->begin(), table->begin()->end(), std::back_inserter(*header));
            table->erase(table->begin());
        }
    }

    template<typename T>
    inline void WriteCsv(const string &file_name, const vector<vector<T>> &table, const string &header = {}) {
        std::ofstream ofs(file_name);
        LOG(INFO) << "Write: " << file_name;

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

    template<class T>
    inline void SaveVar(const string &file_name, const T &var) {
        std::ofstream ofs;
        ofs.open(file_name, std::ios::binary | std::ios::out | std::ios::trunc);
        LOG(INFO) << "Write: " << file_name;

        ofs.write((char *) &var, sizeof(T));
        ofs.close();
    }

    template<class T>
    inline void LoadVar(const string &file_name, T *var) {
        std::ifstream ifs;
        ifs.open(file_name, std::ios::binary | std::ios::in);
        if (!ifs) {
            LOG(FATAL) << "Cannot open csv file: " << file_name;
        } else {
            LOG(INFO) << "Read: " << file_name;
        }

        ifs.read((char *) var, sizeof(T));
        ifs.close();
    }
}

#endif //CSV_IO_H
