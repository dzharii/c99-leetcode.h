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

TEST_CASE("c99lc_string_to_camel_case basic functionality") {
    char buffer[50];

    // Basic camelCase conversion
    size_t result = c99lc_string_to_camel_case("hello world", buffer, 50);
    CHECK(result == 10);
    buffer[result] = '\0'; // null terminate for comparison
    CHECK(std::strcmp(buffer, "helloWorld") == 0);

    // Multiple spaces
    result = c99lc_string_to_camel_case("the quick brown fox", buffer, 50);
    CHECK(result == 16);
    buffer[result] = '\0';
    CHECK(std::strcmp(buffer, "theQuickBrownFox") == 0);

    // Mixed case input
    result = c99lc_string_to_camel_case("MiXeD cAsE", buffer, 50);
    CHECK(result == 9);
    buffer[result] = '\0';
    CHECK(std::strcmp(buffer, "mixedCase") == 0);
}

TEST_CASE("c99lc_string_to_camel_case edge cases") {
    char buffer[50];

    // Empty string
    size_t result = c99lc_string_to_camel_case("", buffer, 50);
    CHECK(result == 0);

    // Only spaces
    result = c99lc_string_to_camel_case("   ", buffer, 50);
    CHECK(result == 0);

    // Single character
    result = c99lc_string_to_camel_case("a", buffer, 50);
    CHECK(result == 1);
    buffer[result] = '\0';
    CHECK(std::strcmp(buffer, "a") == 0);

    // Buffer too small
    result = c99lc_string_to_camel_case("hello world", buffer, 5);
    CHECK(result == 5);
    buffer[result] = '\0';
    CHECK(std::strcmp(buffer, "hello") == 0);

    // NULL inputs
    CHECK(c99lc_string_to_camel_case(nullptr, buffer, 50) == 0);
    CHECK(c99lc_string_to_camel_case("test", nullptr, 50) == 0);
    CHECK(c99lc_string_to_camel_case("test", buffer, 0) == 0);
}

TEST_CASE("c99lc_string_to_camel_case special characters") {
    char buffer[50];

    // Numbers and symbols (should be skipped)
    size_t result = c99lc_string_to_camel_case("hello123 world!", buffer, 50);
    CHECK(result == 10);
    buffer[result] = '\0';
    CHECK(std::strcmp(buffer, "helloWorld") == 0);

    // Leading/trailing spaces
    result = c99lc_string_to_camel_case("  hello world  ", buffer, 50);
    CHECK(result == 10);
    buffer[result] = '\0';
    CHECK(std::strcmp(buffer, "helloWorld") == 0);
}

TEST_CASE("c99lc_stack_char_fla basic operations") {
    c99lc_stack_char_fla* stack = c99lc_stack_char_fla_create(5);
    REQUIRE(stack != nullptr);

    // Initial state
    CHECK(c99lc_stack_char_fla_count(stack) == 0);

    // Push characters
    CHECK(c99lc_stack_char_fla_push(stack, 'a') == true);
    CHECK(c99lc_stack_char_fla_push(stack, 'b') == true);
    CHECK(c99lc_stack_char_fla_push(stack, 'c') == true);
    CHECK(c99lc_stack_char_fla_count(stack) == 3);

    // Pop characters (LIFO order)
    char ch;
    CHECK(c99lc_stack_char_fla_pop(stack, &ch) == true);
    CHECK(ch == 'c');
    CHECK(c99lc_stack_char_fla_pop(stack, &ch) == true);
    CHECK(ch == 'b');
    CHECK(c99lc_stack_char_fla_count(stack) == 1);

    CHECK(c99lc_stack_char_fla_pop(stack, &ch) == true);
    CHECK(ch == 'a');
    CHECK(c99lc_stack_char_fla_count(stack) == 0);

    // Pop from empty stack
    CHECK(c99lc_stack_char_fla_pop(stack, &ch) == false);

    c99lc_stack_char_fla_destroy(stack);
}

TEST_CASE("c99lc_stack_char_fla capacity limits") {
    c99lc_stack_char_fla* stack = c99lc_stack_char_fla_create(2);
    REQUIRE(stack != nullptr);

    // Fill to capacity
    CHECK(c99lc_stack_char_fla_push(stack, 'x') == true);
    CHECK(c99lc_stack_char_fla_push(stack, 'y') == true);

    // Try to exceed capacity
    CHECK(c99lc_stack_char_fla_push(stack, 'z') == false);
    CHECK(c99lc_stack_char_fla_count(stack) == 2);

    c99lc_stack_char_fla_destroy(stack);
}

TEST_CASE("c99lc_stack_char_fla edge cases") {
    // Create with zero capacity
    CHECK(c99lc_stack_char_fla_create(0) == nullptr);

    // Operations on NULL stack
    CHECK(c99lc_stack_char_fla_count(nullptr) == 0);
    CHECK(c99lc_stack_char_fla_push(nullptr, 'a') == false);

    char ch;
    CHECK(c99lc_stack_char_fla_pop(nullptr, &ch) == false);

    // Pop with NULL output
    c99lc_stack_char_fla* stack = c99lc_stack_char_fla_create(1);
    c99lc_stack_char_fla_push(stack, 'a');
    CHECK(c99lc_stack_char_fla_pop(stack, nullptr) == false);

    // Destroy NULL stack (should not crash)
    c99lc_stack_char_fla_destroy(nullptr);
    c99lc_stack_char_fla_destroy(stack);
}

TEST_CASE("c99lc_char_is_open_paren identifies opening parentheses") {
    CHECK(c99lc_char_is_open_paren('(') == true);
    CHECK(c99lc_char_is_open_paren('{') == true);
    CHECK(c99lc_char_is_open_paren('[') == true);

    CHECK(c99lc_char_is_open_paren(')') == false);
    CHECK(c99lc_char_is_open_paren('}') == false);
    CHECK(c99lc_char_is_open_paren(']') == false);
    CHECK(c99lc_char_is_open_paren('a') == false);
    CHECK(c99lc_char_is_open_paren('1') == false);
    CHECK(c99lc_char_is_open_paren('\0') == false);
}

TEST_CASE("c99lc_char_is_close_paren identifies closing parentheses") {
    CHECK(c99lc_char_is_close_paren(')') == true);
    CHECK(c99lc_char_is_close_paren('}') == true);
    CHECK(c99lc_char_is_close_paren(']') == true);

    CHECK(c99lc_char_is_close_paren('(') == false);
    CHECK(c99lc_char_is_close_paren('{') == false);
    CHECK(c99lc_char_is_close_paren('[') == false);
    CHECK(c99lc_char_is_close_paren('a') == false);
    CHECK(c99lc_char_is_close_paren('1') == false);
    CHECK(c99lc_char_is_close_paren('\0') == false);
}

TEST_CASE("c99lc_char_paren_reverse maps parentheses correctly") {
    // Opening to closing
    CHECK(c99lc_char_paren_reverse('(') == ')');
    CHECK(c99lc_char_paren_reverse('{') == '}');
    CHECK(c99lc_char_paren_reverse('[') == ']');

    // Closing to opening
    CHECK(c99lc_char_paren_reverse(')') == '(');
    CHECK(c99lc_char_paren_reverse('}') == '{');
    CHECK(c99lc_char_paren_reverse(']') == '[');

    // Non-parentheses
    CHECK(c99lc_char_paren_reverse('a') == '\0');
    CHECK(c99lc_char_paren_reverse('1') == '\0');
    CHECK(c99lc_char_paren_reverse('\0') == '\0');
    CHECK(c99lc_char_paren_reverse(' ') == '\0');
}

TEST_CASE("parentheses validation using new functions") {
    // Test a simple valid parentheses string using the new stack and helpers
    c99lc_stack_char_fla* stack = c99lc_stack_char_fla_create(100);
    REQUIRE(stack != nullptr);

    const char* test_str = "()[]{}";
    bool is_valid = true;
    char popped_char;

    for (const char* p = test_str; *p && is_valid; p++) {
        if (c99lc_char_is_open_paren(*p)) {
            c99lc_stack_char_fla_push(stack, *p);
        } else if (c99lc_char_is_close_paren(*p)) {
            if (!c99lc_stack_char_fla_pop(stack, &popped_char)) {
                is_valid = false;
            } else if (popped_char != c99lc_char_paren_reverse(*p)) {
                is_valid = false;
            }
        }
    }

    // Stack should be empty for valid parentheses
    is_valid = is_valid && (c99lc_stack_char_fla_count(stack) == 0);
    CHECK(is_valid == true);

    c99lc_stack_char_fla_destroy(stack);
}

TEST_CASE("c99lc_bitset_create allocates and initializes correctly") {
    c99lc_bitset* bitset = c99lc_bitset_create(16);
    REQUIRE(bitset != nullptr);
    CHECK(bitset->bits_capacity == 16);
    CHECK(bitset->bytes_capacity == 2);

    // All bits should be initialized to 0
    for (size_t i = 0; i < 16; ++i) {
        CHECK(c99lc_bitset_test(bitset, i) == false);
    }

    c99lc_bitset_destroy(bitset);
}

TEST_CASE("c99lc_bitset_create with zero capacity returns NULL") {
    c99lc_bitset* bitset = c99lc_bitset_create(0);
    CHECK(bitset == nullptr);
}

TEST_CASE("c99lc_bitset_set and test basic operations") {
    c99lc_bitset* bitset = c99lc_bitset_create(64);
    REQUIRE(bitset != nullptr);

    // Set some bits
    c99lc_bitset_set(bitset, 0);
    c99lc_bitset_set(bitset, 7);
    c99lc_bitset_set(bitset, 15);
    c99lc_bitset_set(bitset, 31);
    c99lc_bitset_set(bitset, 63);

    // Test set bits
    CHECK(c99lc_bitset_test(bitset, 0) == true);
    CHECK(c99lc_bitset_test(bitset, 7) == true);
    CHECK(c99lc_bitset_test(bitset, 15) == true);
    CHECK(c99lc_bitset_test(bitset, 31) == true);
    CHECK(c99lc_bitset_test(bitset, 63) == true);

    // Test unset bits
    CHECK(c99lc_bitset_test(bitset, 1) == false);
    CHECK(c99lc_bitset_test(bitset, 8) == false);
    CHECK(c99lc_bitset_test(bitset, 16) == false);
    CHECK(c99lc_bitset_test(bitset, 32) == false);

    c99lc_bitset_destroy(bitset);
}

TEST_CASE("c99lc_bitset_clear operations") {
    c99lc_bitset* bitset = c99lc_bitset_create(32);
    REQUIRE(bitset != nullptr);

    // Set multiple bits
    for (size_t i = 0; i < 32; ++i) {
        c99lc_bitset_set(bitset, i);
    }

    // Verify all bits are set
    for (size_t i = 0; i < 32; ++i) {
        CHECK(c99lc_bitset_test(bitset, i) == true);
    }

    // Clear some bits
    c99lc_bitset_clear(bitset, 0);
    c99lc_bitset_clear(bitset, 15);
    c99lc_bitset_clear(bitset, 31);

    // Check cleared bits
    CHECK(c99lc_bitset_test(bitset, 0) == false);
    CHECK(c99lc_bitset_test(bitset, 15) == false);
    CHECK(c99lc_bitset_test(bitset, 31) == false);

    // Check remaining set bits
    CHECK(c99lc_bitset_test(bitset, 1) == true);
    CHECK(c99lc_bitset_test(bitset, 16) == true);
    CHECK(c99lc_bitset_test(bitset, 30) == true);

    c99lc_bitset_destroy(bitset);
}

TEST_CASE("c99lc_bitset handles non-power-of-8 capacities") {
    c99lc_bitset* bitset = c99lc_bitset_create(101);
    REQUIRE(bitset != nullptr);
    CHECK(bitset->bits_capacity == 101);
    CHECK(bitset->bytes_capacity == 13); // ceil(101/8) = 13

    // Test edge bits
    c99lc_bitset_set(bitset, 0);
    c99lc_bitset_set(bitset, 100);

    CHECK(c99lc_bitset_test(bitset, 0) == true);
    CHECK(c99lc_bitset_test(bitset, 100) == true);
    CHECK(c99lc_bitset_test(bitset, 50) == false);

    c99lc_bitset_destroy(bitset);
}

TEST_CASE("c99lc_bitset_destroy handles NULL gracefully") {
    c99lc_bitset_destroy(nullptr);
    // Should not crash
    CHECK(true);
}

TEST_CASE("c99lc_bitset used in LeetCode 1748 style problem (sum of unique)") {
    // Simulates the sumOfUnique problem from todo.md
    int nums[] = {1, 2, 3, 2};
    int numsSize = 4;

    c99lc_bitset* seen = c99lc_bitset_create(101);
    c99lc_bitset* removed = c99lc_bitset_create(101);
    REQUIRE(seen != nullptr);
    REQUIRE(removed != nullptr);

    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        if (!c99lc_bitset_test(seen, nums[i])) {
            c99lc_bitset_set(seen, nums[i]);
            sum += nums[i];
        } else {
            if (!c99lc_bitset_test(removed, nums[i])) {
                sum -= nums[i];
                c99lc_bitset_set(removed, nums[i]);
            }
        }
    }

    CHECK(sum == 4); // Only 1 and 3 are unique, 2 appears twice

    c99lc_bitset_destroy(seen);
    c99lc_bitset_destroy(removed);
}

TEST_CASE("c99lc_bitset multiple set operations on same bit are idempotent") {
    c99lc_bitset* bitset = c99lc_bitset_create(8);
    REQUIRE(bitset != nullptr);

    c99lc_bitset_set(bitset, 3);
    c99lc_bitset_set(bitset, 3);
    c99lc_bitset_set(bitset, 3);

    CHECK(c99lc_bitset_test(bitset, 3) == true);

    c99lc_bitset_clear(bitset, 3);
    c99lc_bitset_clear(bitset, 3);

    CHECK(c99lc_bitset_test(bitset, 3) == false);

    c99lc_bitset_destroy(bitset);
}

TEST_CASE("c99lc_array_int_compare works with qsort") {
    int array[] = {5, 2, 8, 1, 9, 3};
    const size_t size = sizeof(array) / sizeof(array[0]);

    qsort(array, size, sizeof(int), c99lc_array_int_compare);

    CHECK(array[0] == 1);
    CHECK(array[1] == 2);
    CHECK(array[2] == 3);
    CHECK(array[3] == 5);
    CHECK(array[4] == 8);
    CHECK(array[5] == 9);
}

TEST_CASE("c99lc_array_int_compare direct comparisons") {
    int a = 5, b = 10, c = 5;

    CHECK(c99lc_array_int_compare(&a, &b) < 0); // a < b
    CHECK(c99lc_array_int_compare(&b, &a) > 0); // b > a
    CHECK(c99lc_array_int_compare(&a, &c) == 0); // a == c
}

TEST_CASE("c99lc_array_int_compare works with negative numbers") {
    int a = -10, b = -5, c = 0, d = 5;

    CHECK(c99lc_array_int_compare(&a, &b) < 0); // -10 < -5
    CHECK(c99lc_array_int_compare(&b, &c) < 0); // -5 < 0
    CHECK(c99lc_array_int_compare(&c, &d) < 0); // 0 < 5
    CHECK(c99lc_array_int_compare(&d, &a) > 0); // 5 > -10
}

TEST_CASE("c99lc_array_int_dedup_sorted basic functionality") {
    int array[] = {1, 1, 2, 3, 3, 3, 4};
    size_t new_size = c99lc_array_int_dedup_sorted(array, 7);

    CHECK(new_size == 4);
    CHECK(array[0] == 1);
    CHECK(array[1] == 2);
    CHECK(array[2] == 3);
    CHECK(array[3] == 4);
}

TEST_CASE("c99lc_array_int_dedup_sorted no duplicates") {
    int array[] = {1, 2, 3, 4, 5};
    size_t new_size = c99lc_array_int_dedup_sorted(array, 5);

    CHECK(new_size == 5);
    CHECK(array[0] == 1);
    CHECK(array[1] == 2);
    CHECK(array[2] == 3);
    CHECK(array[3] == 4);
    CHECK(array[4] == 5);
}

TEST_CASE("c99lc_array_int_dedup_sorted all duplicates") {
    int array[] = {7, 7, 7, 7};
    size_t new_size = c99lc_array_int_dedup_sorted(array, 4);

    CHECK(new_size == 1);
    CHECK(array[0] == 7);
}

TEST_CASE("c99lc_array_int_dedup_sorted edge cases") {
    int single[] = {42};
    CHECK(c99lc_array_int_dedup_sorted(single, 1) == 1);
    CHECK(single[0] == 42);

    CHECK(c99lc_array_int_dedup_sorted(nullptr, 10) == 0);
    CHECK(c99lc_array_int_dedup_sorted(single, 0) == 0);
}

TEST_CASE("c99lc_array_int_diff basic functionality") {
    int source[] = {1, 2, 3, 4, 5};
    int lookup[] = {2, 4}; // sorted
    int out[5];

    size_t count = c99lc_array_int_diff(source, 5, lookup, 2, out);

    CHECK(count == 3);
    CHECK(out[0] == 1);
    CHECK(out[1] == 3);
    CHECK(out[2] == 5);
}

TEST_CASE("c99lc_array_int_diff no differences") {
    int source[] = {1, 2, 3};
    int lookup[] = {1, 2, 3, 4, 5}; // sorted
    int out[3];

    size_t count = c99lc_array_int_diff(source, 3, lookup, 5, out);

    CHECK(count == 0);
}

TEST_CASE("c99lc_array_int_diff all differences") {
    int source[] = {1, 2, 3};
    int lookup[] = {4, 5, 6}; // sorted
    int out[3];

    size_t count = c99lc_array_int_diff(source, 3, lookup, 3, out);

    CHECK(count == 3);
    CHECK(out[0] == 1);
    CHECK(out[1] == 2);
    CHECK(out[2] == 3);
}

TEST_CASE("c99lc_array_int_diff edge cases") {
    int source[] = {1, 2, 3};
    int lookup[] = {2};
    int out[3];

    CHECK(c99lc_array_int_diff(nullptr, 3, lookup, 1, out) == 0);
    CHECK(c99lc_array_int_diff(source, 0, lookup, 1, out) == 0);
    CHECK(c99lc_array_int_diff(source, 3, nullptr, 1, out) == 0);
}

TEST_CASE("c99lc_array_int_diff with negative numbers") {
    int source[] = {-5, -2, 0, 3, 7};
    int lookup[] = {-2, 3}; // sorted
    int out[5];

    size_t count = c99lc_array_int_diff(source, 5, lookup, 2, out);

    CHECK(count == 3);
    CHECK(out[0] == -5);
    CHECK(out[1] == 0);
    CHECK(out[2] == 7);
}

TEST_CASE("LeetCode 2215 findDifference using new helpers") {
    // Simulates the findDifference problem from todo.md
    int nums1[] = {1, 2, 3, 3};
    int nums2[] = {1, 1, 2, 2};
    size_t nums1Size = 4;
    size_t nums2Size = 4;

    // Sort both arrays
    qsort(nums1, nums1Size, sizeof(int), c99lc_array_int_compare);
    qsort(nums2, nums2Size, sizeof(int), c99lc_array_int_compare);

    // Deduplicate
    nums1Size = c99lc_array_int_dedup_sorted(nums1, nums1Size);
    nums2Size = c99lc_array_int_dedup_sorted(nums2, nums2Size);

    // After dedup: nums1 = {1, 2, 3}, nums2 = {1, 2}

    // Find differences
    int result1[3];
    int result2[2];
    size_t result1Size = c99lc_array_int_diff(nums1, nums1Size, nums2, nums2Size, result1);
    size_t result2Size = c99lc_array_int_diff(nums2, nums2Size, nums1, nums1Size, result2);

    // result1 should contain elements in nums1 not in nums2: {3}
    CHECK(result1Size == 1);
    CHECK(result1[0] == 3);

    // result2 should contain elements in nums2 not in nums1: {} (empty)
    CHECK(result2Size == 0);
}

TEST_CASE("c99lc_array_int_diff works with bsearch correctly") {
    // Test that ensures bsearch is working properly
    int source[] = {10, 20, 30, 40, 50};
    int lookup[] = {5, 15, 25, 35, 45}; // sorted, no overlap
    int out[5];

    size_t count = c99lc_array_int_diff(source, 5, lookup, 5, out);

    CHECK(count == 5);
    CHECK(out[0] == 10);
    CHECK(out[1] == 20);
    CHECK(out[2] == 30);
    CHECK(out[3] == 40);
    CHECK(out[4] == 50);
}
