/**
 * For conditional compile
 * @file config.h
 * Copyright 2020 @applejxd
 */
#ifndef SRC_INCLUDE_CONFIG_H_
#define SRC_INCLUDE_CONFIG_H_

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <glog/logging.h>

namespace util {
    using std::string;

    /** 共通ファイル読み込み
     * @tparam T 戻り値の型
     * @param key ini ファイル内のキー
     * @return パラメータ
     */
    template<typename T>
    T GetParam(const std::string &key) {
        static boost::property_tree::ptree pt;

        if (pt.empty()) {
            boost::property_tree::read_ini("config.ini", pt);
            if (pt.empty()) {
                throw std::runtime_error("Cannot open file: config.ini");
            }
        }

        if (boost::optional<T> value = pt.get_optional<T>(key)) {
            LOG(INFO) << "Read param: " << key << " = " << value.get();
            return value.get();
        } else {
            throw std::runtime_error("Cannot get parameter: " + key);
        }
    }

    /** 個別ファイル */
    class Config {
    public:
        explicit Config(const string &file_name) {
            boost::property_tree::read_ini(file_name, pt_);
            if (pt_.empty()) {
                throw std::runtime_error("Cannot open file: " + file_name);
            }
        };

        template<typename T>
        T GetParam(const std::string &key) {
            if (boost::optional<T> value = pt_.get_optional<T>(key)) {
                return value.get();
            } else {
                throw std::runtime_error("Cannot get parameter: " + key);
            }
        }

    private:
        boost::property_tree::ptree pt_;
    };

}   // namespace util

#endif  // SRC_INCLUDE_CONFIG_H_
