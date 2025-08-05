#include "a_leetcode.h"

size_t lc_integers_count_digits(int x) {
    if (x == 0) return 1;
    size_t count = 0;
    if (x < 0) x = -x;
    while(x > 0) {
        x /= 10;
        count++;
    }
    return count;
}


void lc_integers_parse_digits_to_array(int source, unsigned char* dest_array, size_t dest_array_size) {
    size_t i;
    for (i = 0; i < dest_array_size; i++) {
        dest_array[i] = source % 10;
        source = source / 10;
    }
}