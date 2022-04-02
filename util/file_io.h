//
// Created by myama on 2021/11/01.
//

#ifndef CSV_IO_H
#define CSV_IO_H

#include <vector>
#include <string>
#include <stdexcept>
#include <glog/logging.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>

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

        ofs.write((char *) &var, sizeof(var));
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

        ifs.read((char *) var, sizeof(*var));
        ifs.close();
    }

    template<typename T>
    class SerializationWrapper {
    public:
        SerializationWrapper() {}

        SerializationWrapper(const T &var) : var_(var) {}

        T GetVar() { return var_; }

    private:
        T var_;

        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive &ar, unsigned int /*version*/) {
            ar & boost::serialization::make_nvp("var_", var_);
        }
    };

    template<typename T>
    inline void SaveSerializedData(const string &file_name, const T &var) {
        std::ofstream file(file_name);
        boost::archive::text_oarchive ar(file);

        auto data = SerializationWrapper<T>(var);

        ar << boost::serialization::make_nvp("data", data);
    }

    template<typename T>
    inline T LoadSerializedData(const string &file_name) {
        std::ifstream file(file_name);
        boost::archive::text_iarchive ar(file);

        SerializationWrapper<T> data;
        ar >> boost::serialization::make_nvp("data", data);
        return data.GetVar();
    }
}

#endif //CSV_IO_H
