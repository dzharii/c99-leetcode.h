#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
#include "external/doctest/doctest.h"

#include <cstring>
#include <cstdlib>
#include <string>

#define C99_LEETCODE_IMPLEMENTATION
#include "c99-leetcode.h"

TEST_CASE("c99lc_version returns expected semantic version") {
    CHECK(std::strcmp(c99lc_version(), "0.1") == 0);
}

TEST_CASE("c99lc_integers_count_digits handles typical cases") {
    CHECK(c99lc_integers_count_digits(0) == 1);
    CHECK(c99lc_integers_count_digits(9) == 1);
    CHECK(c99lc_integers_count_digits(10) == 2);
    CHECK(c99lc_integers_count_digits(90991) == 5);
    CHECK(c99lc_integers_count_digits(-42) == 2);
}

TEST_CASE("parse and join digits roundtrip") {
    unsigned char buf[6] = {0};
    c99lc_integers_parse_digits_to_array(12345, buf, 6);
    // buf holds {5,4,3,2,1,0}
    CHECK(buf[0] == 5);
    CHECK(buf[1] == 4);
    CHECK(buf[2] == 3);
    CHECK(buf[3] == 2);
    CHECK(buf[4] == 1);
    CHECK(buf[5] == 0);
    CHECK(c99lc_integers_join_digits_from_array(buf, 5) == 12345);
}

TEST_CASE("digits increment big-endian array") {
    unsigned char a1[4] = {0, 0, 9, 9};
    c99lc_digits_increment(a1, 4);
    CHECK(a1[0] == 0);
    CHECK(a1[1] == 1);
    CHECK(a1[2] == 0);
    CHECK(a1[3] == 0);

    unsigned char a2[1] = {9};
    c99lc_digits_increment(a2, 1);
    CHECK(a2[0] == 0);
}

TEST_CASE("digits sum computes total") {
    const unsigned char a[5] = {1, 2, 3, 0, 4};
    CHECK(c99lc_digits_sum(a, 5) == 10);
}

TEST_CASE("bit count and parity") {
    CHECK(c99lc_integers_count_set_bits(0) == 0);
    CHECK(c99lc_integers_count_set_bits(15) == 4);
    CHECK(c99lc_integers_is_even(0) == 1);
    CHECK(c99lc_integers_is_even(7) == 0);
}

TEST_CASE("has zero digit helper") {
    CHECK(c99lc_integers_has_zero_digit(0) == 1);
    CHECK(c99lc_integers_has_zero_digit(10) == 1);
    CHECK(c99lc_integers_has_zero_digit(101) == 1);
    CHECK(c99lc_integers_has_zero_digit(123) == 0);
    CHECK(c99lc_integers_has_zero_digit(-5023) == 1);
    CHECK(c99lc_integers_has_zero_digit(-123) == 0);
}

TEST_CASE("convert integer to sum of two no-zero integers (LeetCode 1317 helper usage)") {
    // Use helper to build a pair a,b such that a+b=n and neither contains digit 0.
    auto find_pair = [](int n, int& out_a, int& out_b) {
        for (int a = 1; a < n; ++a) {
            if (c99lc_integers_has_zero_digit(a)) continue;
            int b = n - a;
            if (!c99lc_integers_has_zero_digit(b)) {
                out_a = a;
                out_b = b;
                return true;
            }
        }
        return false;
    };
    int a = 0, b = 0;
    CHECK(find_pair(11, a, b) == true);
    CHECK(a + b == 11);
    CHECK(c99lc_integers_has_zero_digit(a) == 0);
    CHECK(c99lc_integers_has_zero_digit(b) == 0);

    CHECK(find_pair(101, a, b) == true); // e.g., 2 + 99 = 101
    CHECK(a + b == 101);
    CHECK(c99lc_integers_has_zero_digit(a) == 0);
    CHECK(c99lc_integers_has_zero_digit(b) == 0);
}

TEST_CASE("reverse int array in place") {
    int a[] = {1, 2, 3, 4};
    c99lc_array_int_reverse_in_place(a, 4);
    CHECK(a[0] == 4);
    CHECK(a[1] == 3);
    CHECK(a[2] == 2);
    CHECK(a[3] == 1);
}

TEST_CASE("swap u32 utility") {
    uint32_t a = 1, b = 2;
    c99lc_util_swap_u32(&a, &b);
    CHECK(a == 2);
    CHECK(b == 1);
}

TEST_CASE("parse uint32 from string") {
    uint32_t v = 0;
    CHECK(c99lc_integer_parse_uint32_from_string("12345", 5, &v) == C99LC_RESULT_SUCCESS);
    CHECK(v == 12345u);
    CHECK(c99lc_integer_parse_uint32_from_string("12a", 3, &v) == C99LC_RESULT_FAILED);
}

TEST_CASE("date helpers: leap, dim, parse") {
    CHECK(c99lc_date_is_leap_year(2000) == true);
    CHECK(c99lc_date_is_leap_year(1900) == false);
    CHECK(c99lc_date_is_leap_year(2024) == true);
    CHECK(c99lc_date_days_in_month(2024, 2) == 29u);
    CHECK(c99lc_date_days_in_month(2023, 2) == 28u);

    c99lc_reasonable_date d{};
    CHECK(c99lc_reasonable_date_parse_from_string("2024-02-29", &d) == C99LC_RESULT_SUCCESS);
    CHECK(d.year == 2024u);
    CHECK(d.month == 2u);
    CHECK(d.day == 29u);
    CHECK(c99lc_reasonable_date_parse_from_string("2023-02-29", &d) == C99LC_RESULT_FAILED);
}

TEST_CASE("days since 1971 epoch") {
    c99lc_reasonable_date d1{1971u, 1u, 1u};
    CHECK(c99lc_date_days_since_1971(&d1) == 0u);
    c99lc_reasonable_date d2{1971u, 1u, 2u};
    CHECK(c99lc_date_days_since_1971(&d2) == 1u);
}

TEST_CASE("leaf_values dynamic array push/destroy") {
    c99lc_leaf_values* lv = c99lc_leaf_values_create(0);
    REQUIRE(lv != nullptr);
    c99lc_leaf_values_push(lv, 10);
    c99lc_leaf_values_push(lv, 20);
    c99lc_leaf_values_push(lv, 30);
    CHECK(lv->size == 3);
    CHECK(lv->items[0] == 10);
    CHECK(lv->items[1] == 20);
    CHECK(lv->items[2] == 30);
    c99lc_leaf_values_destroy(lv);
}

TEST_CASE("roman numeral char mapping") {
    CHECK(c99lc_roman_char_to_int('I') == 1);
    CHECK(c99lc_roman_char_to_int('V') == 5);
    CHECK(c99lc_roman_char_to_int('X') == 10);
    CHECK(c99lc_roman_char_to_int('L') == 50);
    CHECK(c99lc_roman_char_to_int('C') == 100);
    CHECK(c99lc_roman_char_to_int('D') == 500);
    CHECK(c99lc_roman_char_to_int('M') == 1000);
    CHECK(c99lc_roman_char_to_int('A') == 0);
}

TEST_CASE("roman to int typical cases") {
    CHECK(c99lc_roman_to_int("III") == 3);
    CHECK(c99lc_roman_to_int("IV") == 4);
    CHECK(c99lc_roman_to_int("IX") == 9);
    CHECK(c99lc_roman_to_int("LVIII") == 58);
    CHECK(c99lc_roman_to_int("MCMXCIV") == 1994);
    CHECK(c99lc_roman_to_int("XLII") == 42);
    CHECK(c99lc_roman_to_int("CM") == 900);
    CHECK(c99lc_roman_to_int("CD") == 400);
    CHECK(c99lc_roman_to_int("") == 0);
}

TEST_CASE("u8 array palindrome helper") {
    CHECK(c99lc_array_u8_is_palindrome(nullptr, 0) == 1);

    const unsigned char p1[1] = {7};
    CHECK(c99lc_array_u8_is_palindrome(p1, 1) == 1);

    const unsigned char p2[4] = {1, 2, 2, 1};
    CHECK(c99lc_array_u8_is_palindrome(p2, 4) == 1);

    const unsigned char p3[5] = {3, 4, 5, 4, 3};
    CHECK(c99lc_array_u8_is_palindrome(p3, 5) == 1);

    const unsigned char np[3] = {1, 2, 3};
    CHECK(c99lc_array_u8_is_palindrome(np, 3) == 0);
}

TEST_CASE("palindrome number via digits + palindrome helper") {
    // Mirror the approach in todo.md but allocation-free and using helpers.
    // For x < 0, not a palindrome.
    auto is_pal_num = [](int x) {
        if (x < 0) return false;
        size_t n = c99lc_integers_count_digits(x);
        unsigned char tmp[20] = {0}; // enough for 32-bit signed int (max 10 digits), padded
        c99lc_integers_parse_digits_to_array(x, tmp, n);
        // tmp is LSB-first; build big-endian view into buf[0..n)
        unsigned char buf[20] = {0};
        for (size_t i = 0; i < n; ++i)
            buf[i] = tmp[n - 1 - i];
        return c99lc_array_u8_is_palindrome(buf, n) == 1;
    };

    CHECK(is_pal_num(0) == true);
    CHECK(is_pal_num(9) == true);
    CHECK(is_pal_num(10) == false);
    CHECK(is_pal_num(121) == true);
    CHECK(is_pal_num(-121) == false);
    CHECK(is_pal_num(123454321) == true);
}

TEST_CASE("interleave halves: shuffle the array examples") {
    {
        int nums[] = {2, 5, 1, 3, 4, 7};
        int out[6] = {0};
        c99lc_array_int_interleave_halves(out, nums, 3);
        CHECK(out[0] == 2);
        CHECK(out[1] == 3);
        CHECK(out[2] == 5);
        CHECK(out[3] == 4);
        CHECK(out[4] == 1);
        CHECK(out[5] == 7);
    }
    {
        int nums[] = {1, 2, 3, 4, 4, 3, 2, 1};
        int out[8] = {0};
        c99lc_array_int_interleave_halves(out, nums, 4);
        int expected[] = {1, 4, 2, 3, 3, 2, 4, 1};
        for (int i = 0; i < 8; ++i)
            CHECK(out[i] == expected[i]);
    }
    {
        int nums[] = {1, 1, 2, 2};
        int out[4] = {0};
        c99lc_array_int_interleave_halves(out, nums, 2);
        int expected[] = {1, 2, 1, 2};
        for (int i = 0; i < 4; ++i)
            CHECK(out[i] == expected[i]);
    }
}

TEST_CASE("add two LSB-first digit arrays typical sums") {
    unsigned char a[3] = {5, 4, 3}; // 345
    unsigned char b[2] = {5, 5}; // 55
    unsigned char out[5] = {0};
    size_t out_size = 0;
    CHECK(c99lc_digits_add_lsb_first(a, 3, b, 2, out, 5, &out_size) == C99LC_RESULT_SUCCESS);
    // 345 + 55 = 400 => digits LSB-first: 0,0,4
    CHECK(out_size == 3);
    CHECK(out[0] == 0);
    CHECK(out[1] == 0);
    CHECK(out[2] == 4);
}

TEST_CASE("add two LSB-first digit arrays with carry producing extra digit") {
    unsigned char a[3] = {9, 9, 9}; // 999
    unsigned char b[1] = {1}; // 1
    unsigned char out[5] = {0};
    size_t out_size = 0;
    CHECK(c99lc_digits_add_lsb_first(a, 3, b, 1, out, 5, &out_size) == C99LC_RESULT_SUCCESS);
    // 999 + 1 = 1000 => digits LSB-first: 0,0,0,1
    CHECK(out_size == 4);
    CHECK(out[0] == 0);
    CHECK(out[1] == 0);
    CHECK(out[2] == 0);
    CHECK(out[3] == 1);
}

TEST_CASE("add two LSB-first digit arrays insufficient capacity fails") {
    unsigned char a[2] = {9, 9}; // 99
    unsigned char b[1] = {1}; // 1
    unsigned char out[2] = {0};
    size_t out_size = 1234; // sentinel to verify unchanged on failure
    CHECK(c99lc_digits_add_lsb_first(a, 2, b, 1, out, 2, &out_size) == C99LC_RESULT_FAILED);
    CHECK(out_size == 1234);
}

TEST_CASE("digits_positive_int_buffer addToArrayForm style sequence") {
    unsigned char n_storage[16] = {0};
    unsigned char k_storage[16] = {0};
    unsigned char sum_storage[16] = {0};
    c99lc_digits_positive_int_buffer nbuf, kbuf, sum;
    REQUIRE(c99lc_digits_positive_int_init(&nbuf, n_storage, 16) == C99LC_RESULT_SUCCESS);
    REQUIRE(c99lc_digits_positive_int_init(&kbuf, k_storage, 16) == C99LC_RESULT_SUCCESS);
    REQUIRE(c99lc_digits_positive_int_init(&sum, sum_storage, 16) == C99LC_RESULT_SUCCESS);
    int num_arr[] = {1, 2, 0, 0};
    REQUIRE(
        c99lc_digits_positive_int_from_big_endian_array(&nbuf, num_arr, 4) == C99LC_RESULT_SUCCESS);
    REQUIRE(c99lc_digits_positive_int_from_int(&kbuf, 34) == C99LC_RESULT_SUCCESS);
    REQUIRE(c99lc_digits_positive_int_add(&nbuf, &kbuf, &sum) == C99LC_RESULT_SUCCESS);
    int out_arr[16] = {0};
    size_t out_n = 0;
    REQUIRE(c99lc_digits_positive_int_to_big_endian_int_array(&sum, out_arr, 16, &out_n) ==
        C99LC_RESULT_SUCCESS);
    CHECK(out_n == 4);
    int expected[] = {1, 2, 3, 4};
    for (size_t i = 0; i < out_n; ++i)
        CHECK(out_arr[i] == expected[i]);
}

TEST_CASE("digits_positive_int_buffer addition carry chain") {
    unsigned char a_store[8] = {0}, b_store[8] = {0}, o_store[8] = {0};
    c99lc_digits_positive_int_buffer a, b, o;
    REQUIRE(c99lc_digits_positive_int_init(&a, a_store, 8) == C99LC_RESULT_SUCCESS);
    REQUIRE(c99lc_digits_positive_int_init(&b, b_store, 8) == C99LC_RESULT_SUCCESS);
    REQUIRE(c99lc_digits_positive_int_init(&o, o_store, 8) == C99LC_RESULT_SUCCESS);
    REQUIRE(c99lc_digits_positive_int_from_int(&a, 999) == C99LC_RESULT_SUCCESS);
    REQUIRE(c99lc_digits_positive_int_from_int(&b, 1) == C99LC_RESULT_SUCCESS);
    REQUIRE(c99lc_digits_positive_int_add(&a, &b, &o) == C99LC_RESULT_SUCCESS);
    int out_arr[8] = {0};
    size_t out_n = 0;
    REQUIRE(c99lc_digits_positive_int_to_big_endian_int_array(&o, out_arr, 8, &out_n) ==
        C99LC_RESULT_SUCCESS);
    CHECK(out_n == 4);
    int expected[] = {1, 0, 0, 0};
    for (size_t i = 0; i < out_n; ++i)
        CHECK(out_arr[i] == expected[i]);
}

TEST_CASE("digits_positive_int_buffer insufficient capacity add fails") {
    unsigned char a_store[2] = {0}, b_store[2] = {0}, o_store[2] = {0};
    c99lc_digits_positive_int_buffer a, b, o;
    REQUIRE(c99lc_digits_positive_int_init(&a, a_store, 2) == C99LC_RESULT_SUCCESS);
    REQUIRE(c99lc_digits_positive_int_init(&b, b_store, 2) == C99LC_RESULT_SUCCESS);
    REQUIRE(c99lc_digits_positive_int_init(&o, o_store, 2) == C99LC_RESULT_SUCCESS);
    REQUIRE(c99lc_digits_positive_int_from_int(&a, 90) == C99LC_RESULT_SUCCESS); // digits 0,9
    REQUIRE(c99lc_digits_positive_int_from_int(&b, 15) == C99LC_RESULT_SUCCESS); // digits 5,1
    // Need capacity 3 for result (105) but out only has 2
    CHECK(c99lc_digits_positive_int_add(&a, &b, &o) == C99LC_RESULT_FAILED);
}
