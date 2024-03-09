#include "variable_diagonal.h"

int** BuildDiagonalArray(size_t lines, size_t columns) {
    const int row_count = static_cast<int>(lines);
    const int col_count = static_cast<int>(columns);
    int** matrix{new int* [row_count] {}};
    for (int i = 0; i < row_count; i++) {
        matrix[i] = new int[col_count]{};
    }
    const int first = 1;
    const int none = 0;
    matrix[none][none] = none;
    int element = 1;
    for (int x = first; x < col_count; ++x) {
        for (int j = x, i = 0; (i < row_count && j >= 0); --j, ++i, ++element) {
            matrix[i][j] = element;
        }
    }
    for (int x = first; x < row_count; ++x) {
        for (int i = x, j = col_count - 1; (i < row_count && j >= 0); --j, ++i, ++element) {
            matrix[i][j] = element;
        }
    }
    return matrix;
}