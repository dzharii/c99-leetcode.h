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
