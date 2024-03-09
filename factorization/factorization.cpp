#include "factorization.h"

std::vector<std::pair<int64_t, int>> Factorize(int64_t x) {
    std::vector<std::pair<int64_t, int>> result;
    for (int64_t i = 2; i * i <= x; ++i) {
        int count = 0;
        while (x % i == 0) {
            x /= i;
            count++;
        }
        if (count > 0) {
            result.emplace_back(i, count);
        }
    }
    if (x > 1) {
        result.emplace_back(x, 1);
    }
    return result;
}