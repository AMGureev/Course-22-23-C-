#include "next_even.h"

int64_t NextEven(int64_t n) {
    if (n % 2 == 0) {
        return n + 2;
    } else {
        return n + 1;
    }
}
