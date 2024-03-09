#include "min_divisor.h"

int64_t MinDivisor(int64_t number) {
    int64_t a = 2;
    int64_t b = number;
    while (b - a > 1) {
        int64_t m = (b + a) / 2;
        if (m * m > number) {
            b = m;
        } else {
            a = m;
        }
    }
    for (int64_t i = 2; i <= b + 1; ++i) {
        if (number % i == 0) {
            return i;
        }
    }
    return number;
}
