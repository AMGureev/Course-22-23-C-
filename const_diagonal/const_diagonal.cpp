#include "const_diagonal.h"

void BuildDiagonalArray(TableType table) {
    int current_value = 0;
    for (int diagonal = 0; diagonal < LINES + COLUMNS - 1; ++diagonal) {
        for (int i = 0; i < LINES; ++i) {
            int j = diagonal - i;
            if (j >= 0 && j < COLUMNS) {
                table[i][j] = current_value;
                current_value++;
            }
        }
    }
}