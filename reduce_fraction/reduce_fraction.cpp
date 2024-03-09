#include "reduce_fraction.h"

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t clone_numerator = numerator;
    int64_t clone_denominator = denominator;
    while (denominator != 0) {
        int64_t temp = numerator % denominator;
        numerator = denominator;
        denominator = temp;
    }
    return clone_numerator / numerator + clone_denominator / numerator;
}
