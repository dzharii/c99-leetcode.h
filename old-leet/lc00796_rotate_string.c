#include "a_leetcode.h"

// https://leetcode.com/problems/rotate-string/?envType=problem-list-v2&envId=n4ywxfx6

inline char get_char(char *s, size_t s_size, size_t index) {
    return s[index % s_size];
}

inline bool strings_equal(char *s, size_t s_size, size_t s_start_index, char* goal) {
    for (size_t i = 0; i < s_size; i++) {
        if (get_char(s, s_size, s_start_index + i) != goal[i]) {
            return false;
        }
    }
    return true;
}

bool rotateString(char* s, char* goal) {
    const size_t s_size = strlen(s);
    const size_t goal_size = strlen(goal);
    if (s_size != goal_size) return false;

    for (size_t i = 0; i < s_size; i++) {
        if (strings_equal(s, s_size, i, goal)) {
            return true;
        }
    }
    return false;
}
