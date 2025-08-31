#include "a_leetcode.h"

// https://leetcode.com/problems/palindrome-number/
bool isPalindrome(int x) {
    if (x < 0) return false;
    size_t total_digits = lc_integers_count_digits(x);
    unsigned char* digits = (unsigned char*)malloc(total_digits);
    lc_integers_parse_digits_to_array(x, digits, total_digits);

    size_t begin = 0;
    size_t end = total_digits - 1;

    bool result = true;

    while (begin < end) {
        if (digits[begin] != digits[end]) {
            result = false;
            break;
        }
        begin += 1;
        end -=1;
    }

    free(digits);
    return result;
}