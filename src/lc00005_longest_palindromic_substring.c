#include "leetcode.h"

// https://leetcode.com/problems/longest-palindromic-substring/
typedef struct {
    const char* value;
    const size_t size;
} string_view;

typedef struct {
    size_t begin_index;
    size_t end_index;
    size_t size;
} range_pair;

inline range_pair range_pair_create(const size_t begin_index, const size_t end_index, const bool is_valid) {
    return (range_pair) {
        .begin_index = begin_index,
        .end_index = end_index,
        .size = is_valid ? (end_index - begin_index + 1) : 0,
    };
}

inline range_pair range_pair_create_invalid_range() {
    return range_pair_create(0, 0, false);
}

inline string_view string_view_create(const char* s) {
    string_view sv = {
        .value = s,
        .size = strlen(s),
    };
    return sv;
}

inline bool string_view_is_valid_index(string_view sv, size_t index) {
    return index < sv.size;
}

char* string_view_substring(string_view sv, size_t begin, size_t length) {
    if (begin >= sv.size) {
        return NULL; // invalid start
    }
    if (begin + length > sv.size) {
        length = sv.size - begin; // clamp to end
    }

    char* copy = malloc(length + 1); // +1 for null terminator
    if (!copy) {
        return NULL; // allocation failed
    }

    memcpy(copy, sv.value + begin, length);
    copy[length] = '\0';

    return copy;
}

// Expands around a given left/right center until mismatch or bounds exceeded
range_pair expand_center(string_view sv, size_t left, size_t right) {
    while (left > 0 && right + 1 < sv.size && sv.value[left - 1] == sv.value[right + 1]) {
        left--;
        right++;
    }
    return range_pair_create(left, right, true);
}

char* longestPalindrome(char* s) {
    string_view sv = string_view_create(s);
    if (sv.size < 2) return strdup(s); // return full string if length 0 or 1

    range_pair max = range_pair_create_invalid_range();

    for (size_t index = 0; index < sv.size; index++) {
        // Odd-length palindrome
        range_pair odd = expand_center(sv, index, index);
        if (odd.size > max.size) max = odd;

        // Even-length palindrome
        if (index + 1 < sv.size && sv.value[index] == sv.value[index + 1]) {
            range_pair even = expand_center(sv, index, index + 1);
            if (even.size > max.size) max = even;
        }
    }

    // No palindrome found, return first character
    if (max.size == 0) {
        return strndup(s, 1);
    }

    return string_view_substring(sv, max.begin_index, max.size);
}