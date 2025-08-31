// c99-leetcode.h - v0.1 - tiny stb-style single-header "Hello, World!" library
// Public Domain or MIT, your choice, see end of file.
//
// Minimal example of the stb single-header pattern.
// No allocations, no dependencies beyond the C standard library.
//
// DOCUMENTATION
//
//   Overview:
//     A trivial API that returns "Hello, World!" either as a const string
//     or by writing it into a caller-provided buffer.
//
//   Defines that control this header:
//     C99_LEETCODE_STATIC
//         Define before including the *implementation* to make function
//         definitions 'static' so each including .c/.cpp gets its own copy.
//     C99_LEETCODE_IMPLEMENTATION
//         Define in exactly one .c/.cpp before including this header to
//         compile the implementation.
//     C99_LEETCODE_NO_STDIO
//         Omit stdio-based sample helpers if you add any that use stdio.
//
//   Build:
//     In one source file:
//         #define C99_LEETCODE_IMPLEMENTATION
//         #include "c99-leetcode.h"
//     In all other files:
//         #include "c99-leetcode.h"
//
//   API:
//     C99_LEETCODE_PUBLIC_DECL const char* c99lc_helloworld(void);
//       Returns a pointer to a constant, null-terminated "Hello, World!".
//
//     C99_LEETCODE_PUBLIC_DECL int c99lc_helloworld_into(char* out, size_t out_cap);
//       Writes "Hello, World!" into 'out' with null-termination.
//       Returns the number of bytes written excluding the terminator.
//       Writes nothing and returns 0 if out is NULL or out_cap == 0.

//   Integer utilities (from todo.md):
//     C99_LEETCODE_PUBLIC_DECL size_t c99lc_integers_count_digits(int x);
//       Returns the number of decimal digits in x (e.g., 0 -> 1, 90991 -> 5).
//
//     C99_LEETCODE_PUBLIC_DECL void c99lc_integers_parse_digits_to_array(int source,
//         unsigned char* dest_array, size_t dest_array_size);
//       Writes decimal digits of 'source' into dest_array in reverse (LSB first).
//
//     C99_LEETCODE_PUBLIC_DECL int c99lc_integers_join_digits_from_array(
//         const unsigned char* src_array, size_t src_array_size);
//       Reconstructs an integer from digits stored LSB-first in src_array.
//
//     C99_LEETCODE_PUBLIC_DECL unsigned char c99lc_integers_is_even(int num);
//       Returns 1 if even, 0 if odd.
//
//     C99_LEETCODE_PUBLIC_DECL int c99lc_integers_count_set_bits(int number);
//       Counts set bits (population count) in the binary representation of number.
//
//     C99_LEETCODE_PUBLIC_DECL void c99lc_digits_increment(unsigned char* digits, size_t digits_size);
//       In-place +1 of big-endian decimal digit array (digits in [0,9], MSB at index 0).
//
//     C99_LEETCODE_PUBLIC_DECL unsigned char c99lc_digits_sum(const unsigned char* digits, size_t digits_size);
//       Sums decimal digits; returns value in [0, 9*digits_size].
//
//     Optional stdio helper (omitted when C99_LEETCODE_NO_STDIO):
//       C99_LEETCODE_PUBLIC_DECL void c99lc_print_integer_array(const unsigned char* a, size_t n);
//       Prints [d0, d1, ...] to stdout.
//
// VERSION HISTORY
//   0.1  Initial release.
//
// CONTRIBUTORS
//   %_YOU_%.
//
// LICENSE
//   See end of file for license information.

#ifndef C99_LEETCODE_H_INCLUDE
#define C99_LEETCODE_H_INCLUDE

#ifdef __cplusplus
extern "C" {
#endif

// Public declaration macro: resolves to extern or extern "C" for C++.
// Users can override by defining c99lc_PUBLIC_DECL before this include.
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

// Standard integer and boolean types
#include <stdint.h>
#include <stdbool.h>

// Optional configuration hooks for future allocation needs.
// Not used by this template, but provided to match stb guidance.
#ifndef C99_LEETCODE_NO_ALLOC
#  include <stddef.h> // size_t for allocator signatures if you use them later
#  ifndef C99_LEETCODE_MALLOC
#    include <stdlib.h>
#    define C99_LEETCODE_MALLOC(ctx, size)        ((void)(ctx), malloc(size))
#    define C99_LEETCODE_FREE(ctx, ptr)           ((void)(ctx), free(ptr))
#    define C99_LEETCODE_REALLOC(ctx, ptr, size)  ((void)(ctx), realloc(ptr, size))
#  endif
#endif

// Public API
C99_LEETCODE_PUBLIC_DECL const char* c99lc_helloworld(void);
C99_LEETCODE_PUBLIC_DECL int         c99lc_helloworld_into(char* out, size_t out_cap);

// Version query, handy for diagnostics.
C99_LEETCODE_PUBLIC_DECL const char* c99lc_version(void);

// Integer utilities (public declarations)
C99_LEETCODE_PUBLIC_DECL size_t       c99lc_integers_count_digits(int x);
C99_LEETCODE_PUBLIC_DECL void         c99lc_integers_parse_digits_to_array(int source, unsigned char* dest_array, size_t dest_array_size);
C99_LEETCODE_PUBLIC_DECL int          c99lc_integers_join_digits_from_array(const unsigned char* src_array, size_t src_array_size);
C99_LEETCODE_PUBLIC_DECL int          c99lc_integers_count_set_bits(int number);
C99_LEETCODE_PUBLIC_DECL unsigned char c99lc_integers_is_even(int num);
C99_LEETCODE_PUBLIC_DECL void         c99lc_digits_increment(unsigned char* digits, size_t digits_size);
C99_LEETCODE_PUBLIC_DECL unsigned char c99lc_digits_sum(const unsigned char* digits, size_t digits_size);
#ifndef C99_LEETCODE_NO_STDIO
C99_LEETCODE_PUBLIC_DECL void         c99lc_print_integer_array(const unsigned char* a, size_t n);
#endif

// Arrays and small utilities
C99_LEETCODE_PUBLIC_DECL void         c99lc_array_int_reverse_in_place(int* array, size_t array_size);
C99_LEETCODE_PUBLIC_DECL void         c99lc_util_swap_u32(uint32_t* a, uint32_t* b);

// Result code
typedef int c99lc_result;
enum { C99LC_RESULT_SUCCESS = 0, C99LC_RESULT_FAILED = 1 };

// Parsing helpers
C99_LEETCODE_PUBLIC_DECL c99lc_result  c99lc_integer_parse_uint32_from_string(const char* input, size_t input_size, uint32_t* out);

// Lightweight dynamic array for ints
typedef struct c99lc_leaf_values {
    size_t size;
    size_t capacity;
    int*   items;
} c99lc_leaf_values;
C99_LEETCODE_PUBLIC_DECL c99lc_leaf_values* c99lc_leaf_values_create(size_t initial_capacity);
C99_LEETCODE_PUBLIC_DECL void               c99lc_leaf_values_push(c99lc_leaf_values* lv, int item);
C99_LEETCODE_PUBLIC_DECL void               c99lc_leaf_values_destroy(c99lc_leaf_values* lv);

// Date helpers
typedef struct c99lc_reasonable_date {
    uint32_t year;
    uint32_t month;
    uint32_t day;
} c99lc_reasonable_date;
C99_LEETCODE_PUBLIC_DECL bool         c99lc_date_is_leap_year(uint32_t year);
C99_LEETCODE_PUBLIC_DECL uint32_t     c99lc_date_days_in_month(uint32_t year, uint32_t month);
C99_LEETCODE_PUBLIC_DECL uint32_t     c99lc_date_days_since_1971(const c99lc_reasonable_date* d);
C99_LEETCODE_PUBLIC_DECL c99lc_result c99lc_reasonable_date_parse_from_string(const char* date_string, c99lc_reasonable_date* out);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // C99_LEETCODE_H_INCLUDE


/*=============================================================================
   IMPLEMENTATION
  =============================================================================*/
#ifdef C99_LEETCODE_IMPLEMENTATION

// Definition macro: empty for global symbols, or 'static' when HELLOWORLD_STATIC.
#ifndef C99_LEETCODE_PUBLIC_DEF
#  ifdef C99_LEETCODE_STATIC
#    define C99_LEETCODE_PUBLIC_DEF static
#  else
#    define C99_LEETCODE_PUBLIC_DEF
#  endif
#endif

// Private namespace prefix 'c99lc__' for internal symbols.
static const char c99lc__hello_literal[] = "Hello, World!";
static const char c99lc__version_literal[] = "0.1";

C99_LEETCODE_PUBLIC_DEF const char* c99lc_helloworld(void)
{
    return c99lc__hello_literal;
}

C99_LEETCODE_PUBLIC_DEF int c99lc_helloworld_into(char* out, size_t out_cap)
{
    if (!out || out_cap == 0) return 0;
    // Simple, dependency-free copy of the known literal.
    // Keep it malloc-free per stb guidance.
    const char* s = c99lc__hello_literal;
    size_t i = 0;
    // Reserve one byte for terminator.
    while (s[i] != '\0' && i + 1 < out_cap) {
        out[i] = s[i];
        ++i;
    }
    out[i < out_cap ? i : out_cap - 1] = '\0';
    return (int)i;
}

C99_LEETCODE_PUBLIC_DEF const char* c99lc_version(void)
{
    return c99lc__version_literal;
}

// ---- Integer utilities implementation -------------------------------------
#include <stddef.h> // size_t

C99_LEETCODE_PUBLIC_DEF size_t c99lc_integers_count_digits(int x)
{
    if (x == 0) return 1u;
    size_t count = 0u;
    if (x < 0) x = -x;
    while (x > 0) { x /= 10; ++count; }
    return count;
}

C99_LEETCODE_PUBLIC_DEF void c99lc_integers_parse_digits_to_array(int source, unsigned char* dest_array, size_t dest_array_size)
{
    if (!dest_array || dest_array_size == 0) return;
    for (size_t i = 0; i < dest_array_size; ++i) {
        int q = source / 10;
        int r = source - q * 10; // avoid % on some compilers for negatives
        if (r < 0) r = -r;
        dest_array[i] = (unsigned char)r;
        source = q;
    }
}

C99_LEETCODE_PUBLIC_DEF int c99lc_integers_join_digits_from_array(const unsigned char* src_array, size_t src_array_size)
{
    if (!src_array || src_array_size == 0) return 0;
    int result = 0;
    for (size_t i = 0; i < src_array_size; ++i) {
        result = result * 10 + (int)src_array[src_array_size - i - 1u];
    }
    return result;
}

C99_LEETCODE_PUBLIC_DEF int c99lc_integers_count_set_bits(int number)
{
    unsigned int n = (unsigned int)number;
    int count = 0;
    while (n) { n &= (n - 1u); ++count; }
    return count;
}

C99_LEETCODE_PUBLIC_DEF unsigned char c99lc_integers_is_even(int num)
{
    return (unsigned char)((num % 2) == 0);
}

C99_LEETCODE_PUBLIC_DEF void c99lc_digits_increment(unsigned char* digits, size_t digits_size)
{
    if (!digits || digits_size == 0) return;
    unsigned char carry = 1u;
    for (size_t i = digits_size; i-- > 0 && carry; ) {
        unsigned char sum = (unsigned char)(digits[i] + carry);
        if (sum >= 10u) { digits[i] = 0u; carry = 1u; }
        else { digits[i] = sum; carry = 0u; }
    }
}

C99_LEETCODE_PUBLIC_DEF unsigned char c99lc_digits_sum(const unsigned char* digits, size_t digits_size)
{
    if (!digits || digits_size == 0) return 0u;
    unsigned int s = 0u;
    for (size_t i = 0; i < digits_size; ++i) s += digits[i];
    return (unsigned char)s;
}

#ifndef C99_LEETCODE_NO_STDIO
#  include <stdio.h>
C99_LEETCODE_PUBLIC_DEF void c99lc_print_integer_array(const unsigned char* a, size_t n)
{
    if (!a) { fputs("[]\n", stdout); return; }
    fputc('[', stdout);
    for (size_t i = 0; i < n; ++i) {
        fprintf(stdout, "%u", (unsigned)a[i]);
        if (i + 1 < n) fputs(", ", stdout);
    }
    fputs("]\n", stdout);
}
#endif

// Arrays and utilities
C99_LEETCODE_PUBLIC_DEF void c99lc_array_int_reverse_in_place(int* array, size_t array_size)
{
    if (!array || array_size == 0) return;
    int* begin = array;
    int* end   = array + array_size - 1;
    while (begin < end) {
        int tmp = *begin;
        *begin = *end;
        *end = tmp;
        ++begin; --end;
    }
}

C99_LEETCODE_PUBLIC_DEF void c99lc_util_swap_u32(uint32_t* a, uint32_t* b)
{
    if (!a || !b) return;
    uint32_t t = *a; *a = *b; *b = t;
}

// Parsing
C99_LEETCODE_PUBLIC_DEF c99lc_result c99lc_integer_parse_uint32_from_string(const char* input, size_t input_size, uint32_t* out)
{
    if (!input || !out || input_size == 0) return C99LC_RESULT_FAILED;
    uint32_t value = 0u;
    for (size_t i = 0; i < input_size; ++i) {
        unsigned char ch = (unsigned char)input[i];
        if (ch < '0' || ch > '9') return C99LC_RESULT_FAILED;
        uint32_t digit = (uint32_t)(ch - '0');
        value = value * 10u + digit;
    }
    *out = value;
    return C99LC_RESULT_SUCCESS;
}

// Dynamic array
C99_LEETCODE_PUBLIC_DEF c99lc_leaf_values* c99lc_leaf_values_create(size_t initial_capacity)
{
    c99lc_leaf_values* result = (c99lc_leaf_values*)C99_LEETCODE_MALLOC(NULL, sizeof(c99lc_leaf_values));
    if (!result) return NULL;
    result->size = 0;
    result->capacity = initial_capacity ? initial_capacity : 1;
    result->items = (int*)C99_LEETCODE_MALLOC(NULL, result->capacity * sizeof *result->items);
    if (!result->items) { C99_LEETCODE_FREE(NULL, result); return NULL; }
    return result;
}

C99_LEETCODE_PUBLIC_DEF void c99lc_leaf_values_push(c99lc_leaf_values* lv, int item)
{
    if (!lv) return;
    if (lv->size == lv->capacity) {
        size_t new_capacity = lv->capacity ? lv->capacity * 2 : 1;
        int* new_items = (int*)C99_LEETCODE_REALLOC(NULL, lv->items, new_capacity * sizeof *lv->items);
        if (!new_items) return; // drop push if realloc fails
        lv->items = new_items;
        lv->capacity = new_capacity;
    }
    lv->items[lv->size++] = item;
}

C99_LEETCODE_PUBLIC_DEF void c99lc_leaf_values_destroy(c99lc_leaf_values* lv)
{
    if (lv) {
        C99_LEETCODE_FREE(NULL, lv->items);
        C99_LEETCODE_FREE(NULL, lv);
    }
}

// Date helpers
C99_LEETCODE_PUBLIC_DEF bool c99lc_date_is_leap_year(uint32_t year)
{
    return ((year % 4u == 0u) && (year % 100u != 0u)) || (year % 400u == 0u);
}

C99_LEETCODE_PUBLIC_DEF uint32_t c99lc_date_days_in_month(uint32_t year, uint32_t month)
{
    static const unsigned char mdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (month < 1u || month > 12u) return 0u;
    unsigned char leap = (month == 2u && c99lc_date_is_leap_year(year)) ? 1u : 0u;
    return (uint32_t)mdays[month - 1u] + (uint32_t)leap;
}

C99_LEETCODE_PUBLIC_DEF uint32_t c99lc_date_days_since_1971(const c99lc_reasonable_date* d)
{
    if (!d) return 0u;
    uint32_t days = 0u;
    for (uint32_t y = 1971u; y < d->year; ++y) days += c99lc_date_is_leap_year(y) ? 366u : 365u;
    for (uint32_t m = 1u; m < d->month; ++m) days += c99lc_date_days_in_month(d->year, m);
    days += (d->day - 1u);
    return days;
}

C99_LEETCODE_PUBLIC_DEF c99lc_result c99lc_reasonable_date_parse_from_string(const char* date_string, c99lc_reasonable_date* out)
{
    if (!date_string || !out) return C99LC_RESULT_FAILED;
    size_t len = 0u; while (date_string[len] != '\0') ++len;
    if (len != 10u) return C99LC_RESULT_FAILED;
    if (date_string[4] != '-' || date_string[7] != '-') return C99LC_RESULT_FAILED;
    if (c99lc_integer_parse_uint32_from_string(date_string, 4, &out->year) != C99LC_RESULT_SUCCESS) return C99LC_RESULT_FAILED;
    if (c99lc_integer_parse_uint32_from_string(date_string + 5, 2, &out->month) != C99LC_RESULT_SUCCESS) return C99LC_RESULT_FAILED;
    if (c99lc_integer_parse_uint32_from_string(date_string + 8, 2, &out->day) != C99LC_RESULT_SUCCESS) return C99LC_RESULT_FAILED;
    if (out->month < 1u || out->month > 12u) return C99LC_RESULT_FAILED;
    uint32_t dim = c99lc_date_days_in_month(out->year, out->month);
    if (dim == 0u || out->day < 1u || out->day > dim) return C99LC_RESULT_FAILED;
    return C99LC_RESULT_SUCCESS;
}

#endif // C99_LEETCODE_IMPLEMENTATION


/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2025 Dmytro Zharii
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
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
the detriment of our heirs and successors. We intend this dedication to be an
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
