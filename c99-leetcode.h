/* c99-leetcode.h - v0.1 - single-header C99 utilities
   Public Domain or MIT, your choice, see end of file.

   Overview
     Tiny stb-style header providing small, dependency-free helpers commonly
     needed in coding challenge style problems: integer digit routines,
     bit counting and parity, array reversal, Roman numeral conversion,
     ASCII decimal parsing, a minimal int vector, and simple date helpers.

   Design
     - Single-header; include this file everywhere.
     - In one translation unit: #define C99_LEETCODE_IMPLEMENTATION before include.
     - Optional C99_LEETCODE_STATIC makes definitions 'static' in that TU.
     - Optional C99_LEETCODE_NO_STDIO omits printf-based helpers.
     - No hidden global state. Allocation hooks are provided but optional.

   Build
     In one source file:
       #define C99_LEETCODE_IMPLEMENTATION
       #include "c99-leetcode.h"
     In all other files:
       #include "c99-leetcode.h"
*/

#ifndef C99_LEETCODE_H_INCLUDE
#define C99_LEETCODE_H_INCLUDE

#ifdef __cplusplus
extern "C" {
#endif

/* Public declaration macro: resolves to extern or extern "C" for C++. */
#ifndef C99_LEETCODE_PUBLIC_DECL
#  ifdef C99_LEETCODE_STATIC
#    define C99_LEETCODE_PUBLIC_DECL static
#  else
#    ifdef __cplusplus
#      define C99_LEETCODE_PUBLIC_DECL extern "C"
#    else
#      define C99_LEETCODE_PUBLIC_DECL extern
#    endif
#  endif
#endif

/* Standard integer and boolean types */
#include <stdint.h>
#include <stdbool.h>

/* Optional configuration hooks for future allocation needs. */
#ifndef C99_LEETCODE_NO_ALLOC
#  include <stddef.h>
#  ifndef C99_LEETCODE_MALLOC
#    include <stdlib.h>
#    define C99_LEETCODE_MALLOC(ctx, size)        ((void)(ctx), malloc(size))
#    define C99_LEETCODE_FREE(ctx, ptr)           ((void)(ctx), free(ptr))
#    define C99_LEETCODE_REALLOC(ctx, ptr, size)  ((void)(ctx), realloc(ptr, size))
#  endif
#endif

/* Public API */

/* Returns a pointer to a constant, null-terminated "Hello, World!" string.
   Storage duration is static; caller must not free the returned pointer. */
C99_LEETCODE_PUBLIC_DECL const char* c99lc_helloworld(void);

/* Copies "Hello, World!" into out and null-terminates.
   Returns bytes written excluding the terminator, or 0 if out is NULL or out_cap is 0. */
C99_LEETCODE_PUBLIC_DECL int c99lc_helloworld_into(char* out, size_t out_cap);

/* Returns the library version string such as "0.1".
   String has static storage duration; caller must not free it. */
C99_LEETCODE_PUBLIC_DECL const char* c99lc_version(void);

/* Integer utilities */

/* Counts the number of decimal digits in x.
   Example: 0 -> 1, 90991 -> 5; ignores the sign for negative inputs. */
C99_LEETCODE_PUBLIC_DECL size_t c99lc_integers_count_digits(int x);

/* Decomposes source into decimal digits written LSB-first into dest_array.
   Writes up to dest_array_size digits; negative numbers produce absolute digits. */
C99_LEETCODE_PUBLIC_DECL void c99lc_integers_parse_digits_to_array(int source, unsigned char* dest_array, size_t dest_array_size);

/* Reconstructs an integer from digits stored LSB-first in src_array.
   Returns 0 if src_array is NULL or src_array_size is 0. */
C99_LEETCODE_PUBLIC_DECL int c99lc_integers_join_digits_from_array(const unsigned char* src_array, size_t src_array_size);

/* Counts set bits (population count) in number treated as unsigned.
   Works for all int values by casting to unsigned during the count. */
C99_LEETCODE_PUBLIC_DECL int c99lc_integers_count_set_bits(int number);

/* Returns 1 if num is even, otherwise 0.
   Handles negative and positive values consistently. */
C99_LEETCODE_PUBLIC_DECL unsigned char c99lc_integers_is_even(int num);

/* Increments a big-endian decimal digit array in place by 1.
   Digits must be in [0,9]; carry ripples from the least significant end. */
C99_LEETCODE_PUBLIC_DECL void c99lc_digits_increment(unsigned char* digits, size_t digits_size);

/* Sums the decimal digits in digits[0..digits_size).
   Returns 0 if digits is NULL or digits_size is 0. */
C99_LEETCODE_PUBLIC_DECL unsigned char c99lc_digits_sum(const unsigned char* digits, size_t digits_size);

#ifndef C99_LEETCODE_NO_STDIO
/* Prints digits as "[d0, d1, ...]\n" to stdout.
   Safe to call with NULL pointer (prints an empty list). */
C99_LEETCODE_PUBLIC_DECL void c99lc_print_integer_array(const unsigned char* a, size_t n);
#endif

/* Arrays and utilities */

/* Reverses array[0..array_size) in place.
   No-op if array is NULL or array_size is 0. */
C99_LEETCODE_PUBLIC_DECL void c99lc_array_int_reverse_in_place(int* array, size_t array_size);

/* Swaps two 32-bit unsigned integers pointed to by a and b.
   No-op if either pointer is NULL. */
C99_LEETCODE_PUBLIC_DECL void c99lc_util_swap_u32(uint32_t* a, uint32_t* b);

/* Result code */
typedef int c99lc_result;
enum { C99LC_RESULT_SUCCESS = 0, C99LC_RESULT_FAILED = 1 };

/* Parsing helpers */

/* Parses ASCII decimal digits from input[0..input_size) into *out.
   Fails on non-digits or empty input; returns a C99LC_RESULT_* code. */
C99_LEETCODE_PUBLIC_DECL c99lc_result c99lc_integer_parse_uint32_from_string(const char* input, size_t input_size, uint32_t* out);

/* Roman numerals */

/* Maps a single Roman numeral character to its integer value.
   Returns 0 for unsupported characters. */
C99_LEETCODE_PUBLIC_DECL int c99lc_roman_char_to_int(char ch);

/* Converts a Roman numeral string using standard subtractive notation.
   Returns 0 for NULL or for a string that contributes no valid symbols. */
C99_LEETCODE_PUBLIC_DECL int c99lc_roman_to_int(const char* s);

/* Lightweight dynamic array for ints */

typedef struct c99lc_leaf_values {
    size_t size;
    size_t capacity;
    int* items;
} c99lc_leaf_values;

/* Allocates a growable array of int with initial_capacity (1 if 0).
   Returns NULL on allocation failure. */
C99_LEETCODE_PUBLIC_DECL c99lc_leaf_values* c99lc_leaf_values_create(size_t initial_capacity);

/* Appends item to the end of the vector, growing capacity as needed.
   If reallocation fails the push is dropped. */
C99_LEETCODE_PUBLIC_DECL void c99lc_leaf_values_push(c99lc_leaf_values* lv, int item);

/* Frees the vector and its storage.
   Safe to call with NULL. */
C99_LEETCODE_PUBLIC_DECL void c99lc_leaf_values_destroy(c99lc_leaf_values* lv);

/* Date helpers */

typedef struct c99lc_reasonable_date {
    uint32_t year;
    uint32_t month;
    uint32_t day;
} c99lc_reasonable_date;

/* Returns true if year is a Gregorian leap year.
   Applies the 4, 100, 400 rule. */
C99_LEETCODE_PUBLIC_DECL bool c99lc_date_is_leap_year(uint32_t year);

/* Returns the number of days in the given month of year.
   Returns 0 if month is out of range 1..12. */
C99_LEETCODE_PUBLIC_DECL uint32_t c99lc_date_days_in_month(uint32_t year, uint32_t month);

/* Counts days since 1971-01-01 for date d.
   Returns 0 if d is NULL; assumes d contains a valid date. */
C99_LEETCODE_PUBLIC_DECL uint32_t c99lc_date_days_since_1971(const c99lc_reasonable_date* d);

/* Parses "YYYY-MM-DD" into out and validates month and day ranges.
   Returns C99LC_RESULT_SUCCESS on success, otherwise C99LC_RESULT_FAILED. */
C99_LEETCODE_PUBLIC_DECL c99lc_result c99lc_reasonable_date_parse_from_string(const char* date_string, c99lc_reasonable_date* out);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* C99_LEETCODE_H_INCLUDE */


/*=============================================================================
   IMPLEMENTATION
  =============================================================================*/
#ifdef C99_LEETCODE_IMPLEMENTATION

/* Definition macro: empty for global symbols, or 'static' when C99_LEETCODE_STATIC. */
#ifndef C99_LEETCODE_PUBLIC_DEF
#  ifdef C99_LEETCODE_STATIC
#    define C99_LEETCODE_PUBLIC_DEF static
#  else
#    define C99_LEETCODE_PUBLIC_DEF
#  endif
#endif

/* Private namespace prefix 'c99lc__' for internal symbols. */
static const char c99lc__hello_literal[]   = "Hello, World!";
static const char c99lc__version_literal[] = "0.1";

C99_LEETCODE_PUBLIC_DEF const char* c99lc_helloworld(void)
{
    return c99lc__hello_literal;
}

C99_LEETCODE_PUBLIC_DEF int c99lc_helloworld_into(char* out, size_t out_cap)
{
    /* Fast-fail if buffer cannot hold even the terminator. */
    const bool has_writable_buffer = (out != NULL) && (out_cap > 0u);
    if (!has_writable_buffer) return 0;

    const char* hello = c99lc__hello_literal;
    size_t write_index = 0u;
    const size_t last_writable_index = out_cap - 1u; /* keep space for '\0' */

    while (hello[write_index] != '\0' && write_index < last_writable_index) {
        out[write_index] = hello[write_index];
        ++write_index;
    }

    out[write_index] = '\0';
    return (int)write_index;
}

C99_LEETCODE_PUBLIC_DEF const char* c99lc_version(void)
{
    return c99lc__version_literal;
}

/* ---- Integer utilities implementation ----------------------------------- */
#include <stddef.h> /* size_t */

C99_LEETCODE_PUBLIC_DEF size_t c99lc_integers_count_digits(int x)
{
    if (x == 0) return 1u;

    size_t digit_count = 0u;
    if (x < 0) x = -x;

    while (x > 0) {
        x /= 10;
        ++digit_count;
    }
    return digit_count;
}

C99_LEETCODE_PUBLIC_DEF void c99lc_integers_parse_digits_to_array(int source, unsigned char* dest_array, size_t dest_array_size)
{
    if (!dest_array || dest_array_size == 0u) return;

    for (size_t i = 0; i < dest_array_size; ++i) {
        const int quotient = source / 10;
        int digit = source - quotient * 10; /* avoids % pitfalls for negatives */
        if (digit < 0) digit = -digit;
        dest_array[i] = (unsigned char)digit;
        source = quotient;
    }
}

C99_LEETCODE_PUBLIC_DEF int c99lc_integers_join_digits_from_array(const unsigned char* src_array, size_t src_array_size)
{
    if (!src_array || src_array_size == 0u) return 0;

    int value = 0;
    for (size_t i = 0; i < src_array_size; ++i) {
        const size_t index_from_msb = (src_array_size - 1u) - i;
        value = value * 10 + (int)src_array[index_from_msb];
    }
    return value;
}

C99_LEETCODE_PUBLIC_DEF int c99lc_integers_count_set_bits(int number)
{
    unsigned int v = (unsigned int)number;
    int bits_set_count = 0;
    while (v != 0u) {
        v &= (v - 1u);
        ++bits_set_count;
    }
    return bits_set_count;
}

C99_LEETCODE_PUBLIC_DEF unsigned char c99lc_integers_is_even(int num)
{
    const bool is_even = ((num % 2) == 0);
    return (unsigned char)(is_even ? 1u : 0u);
}

C99_LEETCODE_PUBLIC_DEF void c99lc_digits_increment(unsigned char* digits, size_t digits_size)
{
    if (!digits || digits_size == 0u) return;

    unsigned char carry = 1u;
    for (size_t i = digits_size; i-- > 0u && carry != 0u; ) {
        const unsigned char sum = (unsigned char)(digits[i] + carry);
        const bool overflowed_base10 = (sum >= 10u);
        digits[i] = overflowed_base10 ? 0u : sum;
        carry = overflowed_base10 ? 1u : 0u;
    }
}

C99_LEETCODE_PUBLIC_DEF unsigned char c99lc_digits_sum(const unsigned char* digits, size_t digits_size)
{
    if (!digits || digits_size == 0u) return 0u;

    unsigned int total = 0u;
    for (size_t i = 0; i < digits_size; ++i) total += digits[i];
    return (unsigned char)total;
}

#ifndef C99_LEETCODE_NO_STDIO
#  include <stdio.h>
C99_LEETCODE_PUBLIC_DEF void c99lc_print_integer_array(const unsigned char* a, size_t n)
{
    if (!a) { fputs("[]\n", stdout); return; }

    fputc('[', stdout);
    for (size_t index = 0; index < n; ++index) {
        fprintf(stdout, "%u", (unsigned)a[index]);
        const bool has_more = (index + 1u) < n;
        if (has_more) fputs(", ", stdout);
    }
    fputs("]\n", stdout);
}
#endif

/* Arrays and utilities */
C99_LEETCODE_PUBLIC_DEF void c99lc_array_int_reverse_in_place(int* array, size_t array_size)
{
    if (!array || array_size == 0u) return;

    int* left  = array;
    int* right = array + array_size - 1u;

    while (left < right) {
        const int tmp = *left;
        *left  = *right;
        *right = tmp;
        ++left;
        --right;
    }
}

C99_LEETCODE_PUBLIC_DEF void c99lc_util_swap_u32(uint32_t* a, uint32_t* b)
{
    if (!a || !b) return;
    const uint32_t tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Parsing */
C99_LEETCODE_PUBLIC_DEF c99lc_result c99lc_integer_parse_uint32_from_string(const char* input, size_t input_size, uint32_t* out)
{
    const bool inputs_valid = (input != NULL) && (out != NULL) && (input_size > 0u);
    if (!inputs_valid) return C99LC_RESULT_FAILED;

    uint32_t value = 0u;
    for (size_t i = 0; i < input_size; ++i) {
        const unsigned char ch = (unsigned char)input[i];
        const bool is_digit = (ch >= '0') && (ch <= '9');
        if (!is_digit) return C99LC_RESULT_FAILED;

        const uint32_t digit = (uint32_t)(ch - '0');
        value = value * 10u + digit;
    }

    *out = value;
    return C99LC_RESULT_SUCCESS;
}

/* Roman numerals */
C99_LEETCODE_PUBLIC_DEF int c99lc_roman_char_to_int(char ch)
{
    switch (ch) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default:  return 0;
    }
}

C99_LEETCODE_PUBLIC_DEF int c99lc_roman_to_int(const char* s)
{
    if (!s) return 0;

    size_t length = 0u;
    while (s[length] != '\0') ++length;
    if (length == 0u) return 0;

    int running_total = 0;
    int prev_value = 0;

    for (size_t i = length; i > 0u; ) {
        --i;
        const int current_value = c99lc_roman_char_to_int(s[i]);
        const bool is_subtractive = (current_value < prev_value);
        running_total += is_subtractive ? -current_value : current_value;
        prev_value = current_value;
    }
    return running_total;
}

/* Dynamic array */
C99_LEETCODE_PUBLIC_DEF c99lc_leaf_values* c99lc_leaf_values_create(size_t initial_capacity)
{
    c99lc_leaf_values* lv = (c99lc_leaf_values*)C99_LEETCODE_MALLOC(NULL, sizeof(c99lc_leaf_values));
    if (!lv) return NULL;

    lv->size = 0u;
    lv->capacity = initial_capacity ? initial_capacity : 1u;
    lv->items = (int*)C99_LEETCODE_MALLOC(NULL, lv->capacity * sizeof *lv->items);

    if (!lv->items) {
        C99_LEETCODE_FREE(NULL, lv);
        return NULL;
    }
    return lv;
}

C99_LEETCODE_PUBLIC_DEF void c99lc_leaf_values_push(c99lc_leaf_values* lv, int item)
{
    if (!lv) return;

    const bool needs_growth = (lv->size == lv->capacity);
    if (needs_growth) {
        const size_t new_capacity = lv->capacity ? (lv->capacity * 2u) : 1u;
        int* grown = (int*)C99_LEETCODE_REALLOC(NULL, lv->items, new_capacity * sizeof *lv->items);
        if (!grown) return; /* drop push if realloc fails */
        lv->items = grown;
        lv->capacity = new_capacity;
    }

    lv->items[lv->size++] = item;
}

C99_LEETCODE_PUBLIC_DEF void c99lc_leaf_values_destroy(c99lc_leaf_values* lv)
{
    if (!lv) return;
    C99_LEETCODE_FREE(NULL, lv->items);
    C99_LEETCODE_FREE(NULL, lv);
}

/* Date helpers */
C99_LEETCODE_PUBLIC_DEF bool c99lc_date_is_leap_year(uint32_t year)
{
    const bool divisible_by_4   = (year % 4u)   == 0u;
    const bool divisible_by_100 = (year % 100u) == 0u;
    const bool divisible_by_400 = (year % 400u) == 0u;

    return (divisible_by_4 && !divisible_by_100) || divisible_by_400;
}

C99_LEETCODE_PUBLIC_DEF uint32_t c99lc_date_days_in_month(uint32_t year, uint32_t month)
{
    static const unsigned char days_in_month_lookup[12] =
        {31,28,31,30,31,30,31,31,30,31,30,31};

    const bool month_out_of_range = (month < 1u) || (month > 12u);
    if (month_out_of_range) return 0u;

    const bool is_february_leap = (month == 2u) && c99lc_date_is_leap_year(year);
    return (uint32_t)days_in_month_lookup[month - 1u] + (uint32_t)(is_february_leap ? 1u : 0u);
}

C99_LEETCODE_PUBLIC_DEF uint32_t c99lc_date_days_since_1971(const c99lc_reasonable_date* d)
{
    if (!d) return 0u;

    uint32_t days_total = 0u;

    for (uint32_t year = 1971u; year < d->year; ++year)
        days_total += c99lc_date_is_leap_year(year) ? 366u : 365u;

    for (uint32_t month = 1u; month < d->month; ++month)
        days_total += c99lc_date_days_in_month(d->year, month);

    days_total += (d->day - 1u);
    return days_total;
}

C99_LEETCODE_PUBLIC_DEF c99lc_result c99lc_reasonable_date_parse_from_string(const char* date_string, c99lc_reasonable_date* out)
{
    if (!date_string || !out) return C99LC_RESULT_FAILED;

    size_t len = 0u;
    while (date_string[len] != '\0') ++len;

    const bool length_is_iso10 = (len == 10u);
    if (!length_is_iso10) return C99LC_RESULT_FAILED;

    const bool has_separators = (date_string[4] == '-') && (date_string[7] == '-');
    if (!has_separators) return C99LC_RESULT_FAILED;

    if (c99lc_integer_parse_uint32_from_string(date_string, 4, &out->year) != C99LC_RESULT_SUCCESS) return C99LC_RESULT_FAILED;
    if (c99lc_integer_parse_uint32_from_string(date_string + 5u, 2, &out->month) != C99LC_RESULT_SUCCESS) return C99LC_RESULT_FAILED;
    if (c99lc_integer_parse_uint32_from_string(date_string + 8u, 2, &out->day) != C99LC_RESULT_SUCCESS) return C99LC_RESULT_FAILED;

    const bool month_valid = (out->month >= 1u) && (out->month <= 12u);
    if (!month_valid) return C99LC_RESULT_FAILED;

    const uint32_t dim = c99lc_date_days_in_month(out->year, out->month);
    const bool day_valid = (dim != 0u) && (out->day >= 1u) && (out->day <= dim);
    if (!day_valid) return C99LC_RESULT_FAILED;

    return C99LC_RESULT_SUCCESS;
}

#endif /* C99_LEETCODE_IMPLEMENTATION */


/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2025 Dmytro Zharii
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication for an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
