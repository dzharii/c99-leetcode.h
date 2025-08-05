#include "a_leetcode.h"

https://leetcode.com/problems/roman-to-integer/description/

int roman_to_int(char ch) {
    switch (ch) {
    case 'I': return 1;
    case 'V': return 5;
    case 'X': return 10;
    case 'L': return 50;
    case 'C': return 100;
    case 'D': return 500;
    case 'M': return 1000;
    default:  return 0; // invalid character
    }
}

int romanToInt(char* s) {
    size_t len = strlen(s);
    if (len == 0) return 0;

    int total = 0;
    int prev = 0; 
    int v;
    size_t i = len;

    while (i --> 0) {
        v = roman_to_int(s[i]);
        if (v < prev) { 
            total -= v;
        } else {
            total += v;
        }
        prev = v;
    }
    return total;
}