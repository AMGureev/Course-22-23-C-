#include "chocolate.h"

bool CanBreakSlices(int height, int width, int slices_amount) {
    if (slices_amount <= height || slices_amount <= width) {
        return true;
    } else {
        return false;
    }
};