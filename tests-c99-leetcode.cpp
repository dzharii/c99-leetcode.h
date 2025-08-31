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
    unsigned char a1[4] = {0,0,9,9};
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
    const unsigned char a[5] = {1,2,3,0,4};
    CHECK(c99lc_digits_sum(a, 5) == 10);
}

TEST_CASE("bit count and parity") {
    CHECK(c99lc_integers_count_set_bits(0) == 0);
    CHECK(c99lc_integers_count_set_bits(15) == 4);
    CHECK(c99lc_integers_is_even(0) == 1);
    CHECK(c99lc_integers_is_even(7) == 0);
}

TEST_CASE("reverse int array in place") {
    int a[] = {1,2,3,4};
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
    c99lc_reasonable_date d1{1971u,1u,1u};
    CHECK(c99lc_date_days_since_1971(&d1) == 0u);
    c99lc_reasonable_date d2{1971u,1u,2u};
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
