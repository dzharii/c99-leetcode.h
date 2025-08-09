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

int lc_integers_join_digits_from_array(const unsigned char* src_array, size_t src_array_size) {
    int result = 0;
    for (size_t i = 0; i < src_array_size; i++) {
        result = result * 10 + src_array[src_array_size - i - 1];
    }
    return result;
}


void lc_print_integer_array(const unsigned char* src_array, size_t src_array_size) {
    printf("[");
    for (size_t i = 0; i < src_array_size; i++) {
        printf("%u", src_array[i]);
        if (i + 1 < src_array_size) {
            printf(", ");
        }
    }
    printf("]\n");
}

// counts set bits (1) using bitwise AND operation
int lc_integers_count_set_bits(int number) {
    int count = 0;
    while (number) {
        count += number & 1;
        number >>= 1;
    }
    return count;
}