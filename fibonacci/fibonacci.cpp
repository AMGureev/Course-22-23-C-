#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    int64_t result = 0;
    int64_t prev = 1;
    if (n == 0) {
        return result;
    }
    for (int64_t i = 1; i <= n; i++) {
        int64_t span = result;
        result += prev;
        prev = span;
    }
    return result;
}
