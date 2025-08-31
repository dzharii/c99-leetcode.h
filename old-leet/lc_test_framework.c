#include "a_leetcode.h"

/* Test framework statistics */
typedef struct
{
    int total_tests;
    int passed_tests;
    int failed_tests;
    bool stop_on_failure;
} lc_test_stats_t;

static lc_test_stats_t g_test_stats = {0, 0, 0, true};

/* Initialize test framework */
void lc_test_init(bool stop_on_failure)
{
    g_test_stats.total_tests = 0;
    g_test_stats.passed_tests = 0;
    g_test_stats.failed_tests = 0;
    g_test_stats.stop_on_failure = stop_on_failure;
    printf("=== Test Framework Initialized ===\n");
}

/* Print test summary */
void lc_test_report(void)
{
    printf("\n=== Test Report ===\n");
    printf("Total tests: %d\n", g_test_stats.total_tests);
    printf("Passed: %d\n", g_test_stats.passed_tests);
    printf("Failed: %d\n", g_test_stats.failed_tests);
    if (g_test_stats.failed_tests == 0)
    {
        printf("All tests passed! ✓\n");
    }
    else
    {
        printf("Some tests failed! ✗\n");
    }
    printf("==================\n");
}

/* String formatting functions */
char *lc_string_format_int_array(int *arr, int size)
{
    if (!arr || size <= 0)
    {
        char *result = malloc(3);
        strcpy(result, "[]");
        return result;
    }

    // Calculate needed size: "[1,2,3]" + null terminator
    int estimated_size = 2; // brackets
    for (int i = 0; i < size; i++)
    {
        estimated_size += snprintf(NULL, 0, "%d", arr[i]);
        if (i < size - 1)
            estimated_size += 1; // comma
    }
    estimated_size += 1; // null terminator

    char *result = malloc(estimated_size);
    strcpy(result, "[");

    for (int i = 0; i < size; i++)
    {
        char temp[32];
        snprintf(temp, sizeof(temp), "%d", arr[i]);
        strcat(result, temp);
        if (i < size - 1)
        {
            strcat(result, ",");
        }
    }
    strcat(result, "]");

    return result;
}

char *lc_string_format_int_array_2d(int **arr, int *columnSizes, int rows)
{
    if (!arr || !columnSizes || rows <= 0)
    {
        char *result = malloc(3);
        strcpy(result, "[]");
        return result;
    }

    // Estimate size needed
    int estimated_size = 2; // outer brackets
    for (int i = 0; i < rows; i++)
    {
        estimated_size += 2; // inner brackets
        if (columnSizes[i] > 0)
        {
            for (int j = 0; j < columnSizes[i]; j++)
            {
                estimated_size += snprintf(NULL, 0, "%d", arr[i][j]);
                if (j < columnSizes[i] - 1)
                    estimated_size += 1; // comma
            }
        }
        if (i < rows - 1)
            estimated_size += 1; // comma between rows
    }
    estimated_size += 1; // null terminator

    char *result = malloc(estimated_size * 2); // extra safety margin
    strcpy(result, "[");

    for (int i = 0; i < rows; i++)
    {
        strcat(result, "[");
        for (int j = 0; j < columnSizes[i]; j++)
        {
            char temp[32];
            snprintf(temp, sizeof(temp), "%d", arr[i][j]);
            strcat(result, temp);
            if (j < columnSizes[i] - 1)
            {
                strcat(result, ",");
            }
        }
        strcat(result, "]");
        if (i < rows - 1)
        {
            strcat(result, ",");
        }
    }
    strcat(result, "]");

    return result;
}

/* Assert functions */
bool lc_test_assert_int(int expected, int actual, const char *test_name, const char *input_description)
{
    g_test_stats.total_tests++;

    printf("Test: %s\n", test_name);
    printf("  Input: %s\n", input_description);

    if (expected == actual)
    {
        printf("  Result: PASS ✓\n");
        g_test_stats.passed_tests++;
        return true;
    }
    else
    {
        printf("  Result: FAIL ✗\n");
        printf("  Expected: %d\n", expected);
        printf("  Actual: %d\n", actual);
        g_test_stats.failed_tests++;

        if (g_test_stats.stop_on_failure)
        {
            printf("Stopping on first failure.\n");
            exit(1);
        }
        return false;
    }
}

bool lc_test_assert_string(const char *expected, const char *actual, const char *test_name, const char *input_description)
{
    g_test_stats.total_tests++;

    printf("Test: %s\n", test_name);
    printf("  Input: %s\n", input_description);

    if ((expected == NULL && actual == NULL) ||
        (expected != NULL && actual != NULL && strcmp(expected, actual) == 0))
    {
        printf("  Result: PASS ✓\n");
        g_test_stats.passed_tests++;
        return true;
    }
    else
    {
        printf("  Result: FAIL ✗\n");
        printf("  Expected: \"%s\"\n", expected ? expected : "NULL");
        printf("  Actual: \"%s\"\n", actual ? actual : "NULL");
        g_test_stats.failed_tests++;

        if (g_test_stats.stop_on_failure)
        {
            printf("Stopping on first failure.\n");
            exit(1);
        }
        return false;
    }
}

bool lc_test_assert_int_array(int *expected, int expected_size, int *actual, int actual_size,
                              const char *test_name, const char *input_description)
{
    g_test_stats.total_tests++;

    printf("Test: %s\n", test_name);
    printf("  Input: %s\n", input_description);

    if (expected_size != actual_size)
    {
        printf("  Result: FAIL ✗\n");
        printf("  Expected size: %d, Actual size: %d\n", expected_size, actual_size);
        g_test_stats.failed_tests++;

        if (g_test_stats.stop_on_failure)
        {
            printf("Stopping on first failure.\n");
            exit(1);
        }
        return false;
    }

    for (int i = 0; i < expected_size; i++)
    {
        if (expected[i] != actual[i])
        {
            printf("  Result: FAIL ✗\n");
            printf("  Arrays differ at index %d: expected %d, actual %d\n", i, expected[i], actual[i]);

            char *expected_str = lc_string_format_int_array(expected, expected_size);
            char *actual_str = lc_string_format_int_array(actual, actual_size);
            printf("  Expected: %s\n", expected_str);
            printf("  Actual: %s\n", actual_str);
            free(expected_str);
            free(actual_str);

            g_test_stats.failed_tests++;

            if (g_test_stats.stop_on_failure)
            {
                printf("Stopping on first failure.\n");
                exit(1);
            }
            return false;
        }
    }

    printf("  Result: PASS ✓\n");
    g_test_stats.passed_tests++;
    return true;
}

bool lc_test_assert_int_array_2d(int **expected, int *expected_column_sizes, int expected_rows,
                                 int **actual, int *actual_column_sizes, int actual_rows,
                                 const char *test_name, const char *input_description)
{
    g_test_stats.total_tests++;

    printf("Test: %s\n", test_name);
    printf("  Input: %s\n", input_description);

    if (expected_rows != actual_rows)
    {
        printf("  Result: FAIL ✗\n");
        printf("  Expected rows: %d, Actual rows: %d\n", expected_rows, actual_rows);
        g_test_stats.failed_tests++;

        if (g_test_stats.stop_on_failure)
        {
            printf("Stopping on first failure.\n");
            exit(1);
        }
        return false;
    }

    for (int i = 0; i < expected_rows; i++)
    {
        if (expected_column_sizes[i] != actual_column_sizes[i])
        {
            printf("  Result: FAIL ✗\n");
            printf("  Row %d: Expected columns: %d, Actual columns: %d\n",
                   i, expected_column_sizes[i], actual_column_sizes[i]);
            g_test_stats.failed_tests++;

            if (g_test_stats.stop_on_failure)
            {
                printf("Stopping on first failure.\n");
                exit(1);
            }
            return false;
        }

        for (int j = 0; j < expected_column_sizes[i]; j++)
        {
            if (expected[i][j] != actual[i][j])
            {
                printf("  Result: FAIL ✗\n");
                printf("  Arrays differ at [%d][%d]: expected %d, actual %d\n",
                       i, j, expected[i][j], actual[i][j]);

                char *expected_str = lc_string_format_int_array_2d(expected, expected_column_sizes, expected_rows);
                char *actual_str = lc_string_format_int_array_2d(actual, actual_column_sizes, actual_rows);
                printf("  Expected: %s\n", expected_str);
                printf("  Actual: %s\n", actual_str);
                free(expected_str);
                free(actual_str);

                g_test_stats.failed_tests++;

                if (g_test_stats.stop_on_failure)
                {
                    printf("Stopping on first failure.\n");
                    exit(1);
                }
                return false;
            }
        }
    }

    printf("  Result: PASS ✓\n");
    g_test_stats.passed_tests++;
    return true;
}

/* Helper function to free 2D array */
void lc_test_free_2d_array(int **arr, int rows)
{
    if (!arr)
        return;
    for (int i = 0; i < rows; i++)
    {
        if (arr[i])
            free(arr[i]);
    }
    free(arr);
}
