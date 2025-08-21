#include "a_leetcode.h"

/**
 * @brief Counts the number of digits in an integer.
 *
 * @param x Integer value to evaluate.
 * @return size_t Number of decimal digits in the integer.
 */
size_t lc_integers_count_digits(int x)
{
    if (x == 0)
        return 1;
    size_t count = 0;
    if (x < 0)
        x = -x;
    while (x > 0)
    {
        x /= 10;
        count++;
    }
    return count;
}

/**
 * @brief Splits an integer into its digits and stores them in reverse order.
 *
 * @param source Integer to split.
 * @param dest_array Destination array for digits.
 * @param dest_array_size Size of the destination array.
 */
void lc_integers_parse_digits_to_array(int source, unsigned char *dest_array, size_t dest_array_size)
{
    size_t i;
    for (i = 0; i < dest_array_size; i++)
    {
        dest_array[i] = source % 10;
        source = source / 10;
    }
}

/**
 * @brief Combines digits from an array into a single integer.
 *
 * @param src_array Array containing digits.
 * @param src_array_size Number of digits in the array.
 * @return int Integer formed by combining the digits.
 */
int lc_integers_join_digits_from_array(const unsigned char *src_array, size_t src_array_size)
{
    int result = 0;
    for (size_t i = 0; i < src_array_size; i++)
    {
        result = result * 10 + src_array[src_array_size - i - 1];
    }
    return result;
}

/**
 * @brief Increments a big-endian decimal digits array by 1 in place.
 *
 * @param digits Pointer to an array holding decimal digits in [0,9], MSB at index 0.
 * @param digits_size Number of elements in the digits array.
 */
void digits_increment(uint8_t *digits, size_t digits_size)
{
    uint8_t carry = 1;
    for (size_t i = digits_size; i-- > 0 && carry;)
    {
        uint8_t sum = digits[i] + carry;
        if (sum == 10)
        {
            digits[i] = 0;
            carry = 1;
        }
        else
        {
            digits[i] = sum;
            carry = 0;
        }
    }
}

/**
 * @brief Computes the sum of all decimal digits in a digits array.
 *
 * @param digits Pointer to an array holding decimal digits in [0,9].
 * @param digits_size Number of elements in the digits array.
 * @return uint8_t Sum of the digits in the range [0, 9 * digits_size].
 */
uint8_t digits_sum(uint8_t *digits, size_t digits_size)
{
    uint16_t sum = 0;
    for (size_t i = 0; i < digits_size; i++)
    {
        sum += digits[i];
    }
    return (uint8_t)sum;
}

/**
 * @brief Prints an integer array in a formatted style.
 *
 * @param src_array Array to print.
 * @param src_array_size Number of elements in the array.
 */
void lc_print_integer_array(const unsigned char *src_array, size_t src_array_size)
{
    printf("[");
    for (size_t i = 0; i < src_array_size; i++)
    {
        printf("%u", src_array[i]);
        if (i + 1 < src_array_size)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

/**
 * @brief Counts the number of bits set to 1 in an integer.
 *
 * @param number Integer to evaluate.
 * @return int Number of set bits in the integer.
 */
int lc_integers_count_set_bits(int number)
{
    unsigned int n = (unsigned int)number;
    int count = 0;
    while (n)
    {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

/**
 * @brief Reverses the elements of an integer array in place.
 *
 * @param array Array to reverse.
 * @param array_size Number of elements in the array.
 */
inline static void lc_array_int_reverse_in_place(int *array, size_t array_size)
{
    int *begin = array;
    int *end = array + array_size - 1;
    int tmp;
    while (begin < end)
    {
        tmp = *begin;
        *begin = *end;
        *end = tmp;
        begin++;
        end--;
    }
}

/**
 * @struct leaf_values
 * @brief Dynamic array structure for integers.
 */
typedef struct
{
    size_t size;
    size_t capacity;
    int *items;
} leaf_values;

/**
 * @brief Creates a new dynamic array for integers.
 *
 * @param initial_capacity Initial capacity of the array.
 * @return leaf_values* Pointer to the created dynamic array.
 */
leaf_values *leaf_values_create(size_t initial_capacity)
{
    leaf_values *result = malloc(sizeof(leaf_values));
    result->size = 0;
    result->capacity = initial_capacity ? initial_capacity : 1;
    result->items = malloc(result->capacity * sizeof *result->items);
    return result;
}

/**
 * @brief Adds a new integer to the dynamic array.
 *
 * @param lv Pointer to the dynamic array.
 * @param item Integer to add.
 */
void leaf_values_push(leaf_values *lv, int item)
{
    if (lv->size == lv->capacity)
    {
        size_t new_capacity = lv->capacity * 2;
        lv->items = realloc(lv->items, new_capacity * sizeof *lv->items);
        lv->capacity = new_capacity;
    }
    lv->items[lv->size++] = item;
}

/**
 * @brief Destroys a dynamic array and frees its memory.
 *
 * @param lv Pointer to the dynamic array.
 */
void leaf_values_destroy(leaf_values *lv)
{
    if (lv)
    {
        free(lv->items);
        free(lv);
    }
}

/**
 * @struct Reasonable_Date
 * @brief Simple date representation with year, month, and day components.
 */
typedef struct
{
    uint32_t year;
    uint32_t month;
    uint32_t day;
} Reasonable_Date;

/**
 * @typedef Leet_Result
 * @brief Result code for utility functions.
 *
 * LEET_RESULT_SUCCESS equals 0 and indicates success.
 * LEET_RESULT_FAILED equals 1 and indicates failure.
 */
typedef int Leet_Result;
enum
{
    LEET_RESULT_SUCCESS = 0,
    LEET_RESULT_FAILED = 1
};

/**
 * @brief Parses an unsigned 32-bit integer from an ASCII decimal substring.
 *
 * @param input Pointer to the ASCII buffer.
 * @param input_size Number of characters to parse from input.
 * @param out Pointer to the result variable.
 * @return Leet_Result LEET_RESULT_SUCCESS on success, LEET_RESULT_FAILED on invalid input.
 */
Leet_Result lc_integer_parse_uint32_from_string(const char *input, size_t input_size, uint32_t *out)
{
    if (!input || !out || input_size == 0)
        return LEET_RESULT_FAILED;

    uint32_t value = 0;

    for (size_t i = 0; i < input_size; i++)
    {
        uint8_t ch = (uint8_t)input[i];
        if (ch < '0' || ch > '9')
            return LEET_RESULT_FAILED;

        uint32_t digit = (uint32_t)(ch - '0');
        value = value * 10u + digit;
    }

    *out = value;
    return LEET_RESULT_SUCCESS;
}

/**
 * @brief Deprecated misspelled alias kept for compatibility.
 *
 * Prefer lc_integer_parse_uint32_from_string instead.
 */
Leet_Result lc_integer_parase_uint32_from_string(const char *input, size_t input_size, uint32_t *out)
{
    return lc_integer_parse_uint32_from_string(input, input_size, out);
}

/**
 * @brief Parses a date string in YYYY-MM-DD format into a Reasonable_Date.
 *
 * Performs basic sanity checks on ranges, including leap-aware month lengths.
 *
 * @param date_string Zero-terminated string in the format YYYY-MM-DD.
 * @param out Pointer to the output Reasonable_Date.
 * @return Leet_Result LEET_RESULT_SUCCESS on success, LEET_RESULT_FAILED on invalid input.
 */
Leet_Result lc_reasonable_date_parse_from_string(const char *date_string, Reasonable_Date *out)
{
    if (!date_string || !out)
        return LEET_RESULT_FAILED;

    size_t len = strlen(date_string);
    if (len != 10)
        return LEET_RESULT_FAILED;
    if (date_string[4] != '-' || date_string[7] != '-')
        return LEET_RESULT_FAILED;

    if (lc_integer_parse_uint32_from_string(date_string, 4, &out->year) != LEET_RESULT_SUCCESS)
        return LEET_RESULT_FAILED;

    if (lc_integer_parse_uint32_from_string(date_string + 5, 2, &out->month) != LEET_RESULT_SUCCESS)
        return LEET_RESULT_FAILED;

    if (lc_integer_parse_uint32_from_string(date_string + 8, 2, &out->day) != LEET_RESULT_SUCCESS)
        return LEET_RESULT_FAILED;

    if (out->month < 1 || out->month > 12)
        return LEET_RESULT_FAILED;

    uint32_t dim = 0;
    {
        static const uint8_t mdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        uint8_t leap_days = (out->month == 2 && (((out->year % 4 == 0) && (out->year % 100 != 0)) || (out->year % 400 == 0))) ? 1 : 0;
        dim = (uint32_t)mdays[out->month - 1] + (uint32_t)leap_days;
    }

    if (out->day < 1 || out->day > dim)
        return LEET_RESULT_FAILED;

    return LEET_RESULT_SUCCESS;
}

/**
 * @brief Determines whether a given year is a leap year.
 *
 * @param year Four-digit year.
 * @return bool true if the year is a leap year, false otherwise.
 */
bool lc_date_is_leap_year(uint32_t year)
{
    return ((year % 4u == 0u) && (year % 100u != 0u)) || (year % 400u == 0u);
}

/**
 * @brief Returns the number of days in a given month of a given year.
 *
 * @param year Four-digit year.
 * @param month Month number in range 1..12.
 * @return uint32_t Number of days in the specified month, or 0 if month is out of range.
 */
uint32_t lc_date_days_in_month(uint32_t year, uint32_t month)
{
    static const uint8_t mdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month < 1u || month > 12u)
        return 0u;

    uint8_t leap_days = (month == 2u && lc_date_is_leap_year(year)) ? 1u : 0u;
    return (uint32_t)mdays[month - 1u] + (uint32_t)leap_days;
}

/**
 * @brief Computes the number of days elapsed since 1971-01-01 for a given date.
 *
 * The epoch used is 1971-01-01 which yields 0 for that date.
 * The function assumes the input date fields describe a valid date.
 *
 * @param d Pointer to a Reasonable_Date.
 * @return uint32_t Number of days since 1971-01-01.
 */
uint32_t lc_date_days_since_1971(const Reasonable_Date *d)
{
    uint32_t days = 0;

    for (uint32_t y = 1971u; y < d->year; ++y)
    {
        days += lc_date_is_leap_year(y) ? 366u : 365u;
    }

    for (uint32_t m = 1u; m < d->month; ++m)
    {
        days += lc_date_days_in_month(d->year, m);
    }

    days += (d->day - 1u);
    return days;
}


