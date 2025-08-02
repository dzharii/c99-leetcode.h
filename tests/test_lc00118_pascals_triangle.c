#include "leetcode.h"

// https://leetcode.com/problems/pascals-triangle/description/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int* pascal_triangle_row_elements_alloc(size_t row_number) {
    int* mem = (int*)malloc(sizeof(int) * row_number);
    return mem;
}

struct pascal_triange_sizes_t {
    int* returnSize;
    int** returnColumnSizes;
    int** triangle;
};
typedef struct pascal_triange_sizes_t pascal_triange_sizes_t;

struct pascal_triange_sizes_t pascal_triange_alloc(size_t rows) {
    struct pascal_triange_sizes_t out;
    size_t i;

    out.triangle = (int**)malloc(sizeof(int*) * rows);
    for (i = 0; i < rows; ++i) {
        out.triangle[i] = pascal_triangle_row_elements_alloc(i + 1);
    }

    out.returnSize = (int*)malloc(sizeof(int));
    *out.returnSize = (int)rows;

    out.returnColumnSizes = (int**)malloc(sizeof(int*));
    *out.returnColumnSizes = (int*)malloc(sizeof(int) * rows);
    for (i = 0; i < rows; ++i) {
        (*out.returnColumnSizes)[i] = (int)(i + 1);
    }

    return out;
}

int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    size_t i, j;
    size_t row_end_index;

    struct pascal_triange_sizes_t s = pascal_triange_alloc((size_t)numRows);
    int** triangle = s.triangle;

    /* assign outputs; note the indirection */
    *returnSize = *s.returnSize;
    *returnColumnSizes = *s.returnColumnSizes;

    /* row 1 */
    triangle[0][0] = 1;
    if (numRows == 1) return triangle;

    /* row 2 */
    triangle[1][0] = 1;
    triangle[1][1] = 1;
    if (numRows == 2) return triangle;

    /* rows 3..numRows */
    for (i = 2; i < (size_t)numRows; i++) {
        row_end_index = i;

        triangle[i][0] = 1;
        triangle[i][row_end_index] = 1;

        for (j = 1; j < row_end_index; j++) {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
    }
    return triangle;
}
