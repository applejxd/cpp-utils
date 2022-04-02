//
// Created by myama on 2021/11/01.
//

#ifndef TYPE_H
#define TYPE_H

#include <cfloat>

namespace util {
    bool IsClose(float a, float b) {
        if (std::fabs(a - b) < FLT_EPSILON) {
            return true;
        } else {
            return false;
        }
    }

    bool IsClose(double a, double b) {
        if (std::fabs(a - b) < DBL_EPSILON) {
            return true;
        } else {
            return false;
        }
    }
}   // namespace util

#endif //TYPE_H
