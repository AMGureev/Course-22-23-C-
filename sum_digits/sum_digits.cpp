#include "sum_digits.h"

int64_t SumOfDigits(int64_t number) {
    const int64_t ten = 10;
    int64_t result = 0;
    while (number > 0) {
        result += number % ten;
        number /= ten;
    }
    return result;
}
