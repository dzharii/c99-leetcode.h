
int **generate(int numRows, int *returnSize, int **returnColumnSizes);
#include "lc00118_pascals_triangle.c"
#include "lc_test_framework.c"

/* Helper function to create expected 2D array for testing */
int **create_expected_pascal_triangle(int numRows, int *returnColumnSizes)
{
    int **expected = (int **)malloc(sizeof(int *) * numRows);

    for (int i = 0; i < numRows; i++)
    {
        returnColumnSizes[i] = i + 1;
        expected[i] = (int *)malloc(sizeof(int) * (i + 1));

        // Fill Pascal's triangle values
        expected[i][0] = 1; // First element is always 1
        expected[i][i] = 1; // Last element is always 1

        for (int j = 1; j < i; j++)
        {
            expected[i][j] = expected[i - 1][j - 1] + expected[i - 1][j];
        }
    }

    return expected;
}

void test_pascal_triangle_numRows_1()
{
    int returnSize;
    int *returnColumnSizes;
    int **result = generate(1, &returnSize, &returnColumnSizes);

    // Expected result for numRows = 1: [[1]]
    int *expected_column_sizes = (int *)malloc(sizeof(int) * 1);
    int **expected = create_expected_pascal_triangle(1, expected_column_sizes);

    lc_test_assert_int(1, returnSize, "Pascal Triangle numRows=1 - returnSize", "numRows=1");
    lc_test_assert_int_array_2d(expected, expected_column_sizes, 1,
                                result, returnColumnSizes, returnSize,
                                "Pascal Triangle numRows=1 - triangle", "numRows=1");

    // Cleanup
    lc_test_free_2d_array(expected, 1);
    lc_test_free_2d_array(result, returnSize);
    free(expected_column_sizes);
    free(returnColumnSizes);
}

void test_pascal_triangle_numRows_2()
{
    int returnSize;
    int *returnColumnSizes;
    int **result = generate(2, &returnSize, &returnColumnSizes);

    // Expected result for numRows = 2: [[1], [1,1]]
    int *expected_column_sizes = (int *)malloc(sizeof(int) * 2);
    int **expected = create_expected_pascal_triangle(2, expected_column_sizes);

    lc_test_assert_int(2, returnSize, "Pascal Triangle numRows=2 - returnSize", "numRows=2");
    lc_test_assert_int_array_2d(expected, expected_column_sizes, 2,
                                result, returnColumnSizes, returnSize,
                                "Pascal Triangle numRows=2 - triangle", "numRows=2");

    // Cleanup
    lc_test_free_2d_array(expected, 2);
    lc_test_free_2d_array(result, returnSize);
    free(expected_column_sizes);
    free(returnColumnSizes);
}

void test_pascal_triangle_numRows_3()
{
    int returnSize;
    int *returnColumnSizes;
    int **result = generate(3, &returnSize, &returnColumnSizes);

    // Expected result for numRows = 3: [[1], [1,1], [1,2,1]]
    int *expected_column_sizes = (int *)malloc(sizeof(int) * 3);
    int **expected = create_expected_pascal_triangle(3, expected_column_sizes);

    lc_test_assert_int(3, returnSize, "Pascal Triangle numRows=3 - returnSize", "numRows=3");
    lc_test_assert_int_array_2d(expected, expected_column_sizes, 3,
                                result, returnColumnSizes, returnSize,
                                "Pascal Triangle numRows=3 - triangle", "numRows=3");

    // Cleanup
    lc_test_free_2d_array(expected, 3);
    lc_test_free_2d_array(result, returnSize);
    free(expected_column_sizes);
    free(returnColumnSizes);
}

void test_pascal_triangle_numRows_5()
{
    int returnSize;
    int *returnColumnSizes;
    int **result = generate(5, &returnSize, &returnColumnSizes);

    // Expected result for numRows = 5: [[1], [1,1], [1,2,1], [1,3,3,1], [1,4,6,4,1]]
    int *expected_column_sizes = (int *)malloc(sizeof(int) * 5);
    int **expected = create_expected_pascal_triangle(5, expected_column_sizes);

    lc_test_assert_int(5, returnSize, "Pascal Triangle numRows=5 - returnSize", "numRows=5");
    lc_test_assert_int_array_2d(expected, expected_column_sizes, 5,
                                result, returnColumnSizes, returnSize,
                                "Pascal Triangle numRows=5 - triangle", "numRows=5");

    // Test specific values
    lc_test_assert_int(1, result[0][0], "Pascal Triangle numRows=5 - row 0", "numRows=5, result[0][0]");
    lc_test_assert_int(2, result[2][1], "Pascal Triangle numRows=5 - row 2 middle", "numRows=5, result[2][1]");
    lc_test_assert_int(6, result[4][2], "Pascal Triangle numRows=5 - row 4 middle", "numRows=5, result[4][2]");

    // Cleanup
    lc_test_free_2d_array(expected, 5);
    lc_test_free_2d_array(result, returnSize);
    free(expected_column_sizes);
    free(returnColumnSizes);
}

void test_pascal_triangle_column_sizes()
{
    int returnSize;
    int *returnColumnSizes;
    int **result = generate(4, &returnSize, &returnColumnSizes);

    // Test that column sizes are correct: [1, 2, 3, 4]
    int expected_column_sizes[] = {1, 2, 3, 4};

    lc_test_assert_int_array(expected_column_sizes, 4, returnColumnSizes, returnSize,
                             "Pascal Triangle numRows=4 - column sizes", "numRows=4");

    // Cleanup
    lc_test_free_2d_array(result, returnSize);
    free(returnColumnSizes);
}

void test_pascal_triangle_edge_case_large()
{
    int returnSize;
    int *returnColumnSizes;
    int **result = generate(8, &returnSize, &returnColumnSizes);

    // Test specific known values in row 7 (0-indexed): [1, 7, 21, 35, 35, 21, 7, 1]
    lc_test_assert_int(8, returnSize, "Pascal Triangle numRows=8 - returnSize", "numRows=8");
    lc_test_assert_int(1, result[7][0], "Pascal Triangle numRows=8 - row 7 first", "numRows=8, result[7][0]");
    lc_test_assert_int(7, result[7][1], "Pascal Triangle numRows=8 - row 7 second", "numRows=8, result[7][1]");
    lc_test_assert_int(21, result[7][2], "Pascal Triangle numRows=8 - row 7 third", "numRows=8, result[7][2]");
    lc_test_assert_int(35, result[7][3], "Pascal Triangle numRows=8 - row 7 fourth", "numRows=8, result[7][3]");
    lc_test_assert_int(35, result[7][4], "Pascal Triangle numRows=8 - row 7 fifth", "numRows=8, result[7][4]");
    lc_test_assert_int(21, result[7][5], "Pascal Triangle numRows=8 - row 7 sixth", "numRows=8, result[7][5]");
    lc_test_assert_int(7, result[7][6], "Pascal Triangle numRows=8 - row 7 seventh", "numRows=8, result[7][6]");
    lc_test_assert_int(1, result[7][7], "Pascal Triangle numRows=8 - row 7 last", "numRows=8, result[7][7]");

    // Cleanup
    lc_test_free_2d_array(result, returnSize);
    free(returnColumnSizes);
}

int main()
{
    lc_test_init(true); // Stop on first failure

    printf("Running Pascal's Triangle Tests...\n\n");

    test_pascal_triangle_numRows_1();
    test_pascal_triangle_numRows_2();
    test_pascal_triangle_numRows_3();
    test_pascal_triangle_numRows_5();
    test_pascal_triangle_column_sizes();
    test_pascal_triangle_edge_case_large();

    lc_test_report();

    return g_test_stats.failed_tests == 0 ? 0 : 1;
}