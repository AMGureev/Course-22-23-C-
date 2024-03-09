#include "range.h"

std::vector<int> Range(int from, int to, int step) {
    std::vector<int> result;
    if (step == 0) {
        return result;
    }
    if (step > 0) {
        for (int i = from; i < to; i += step) {
            result.push_back(i);
        }
    } else {
        for (int i = from; i > to; i += step) {
            result.push_back(i);
        }
    }
    return result;
}