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
    // reinterpret bits to avoid runtime error: signed integer overflow
    unsigned int n = (unsigned int)number; 
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}




typedef struct {
    size_t size;
    size_t capacity;
    int* items;
} leaf_values;

///// BEGIN OF MY OWN DYNAMIC ARRAY aka LIST!
leaf_values* leaf_values_create(size_t initial_capacity) {
    leaf_values* result = malloc(sizeof(leaf_values));
    result->size = 0;
    result->capacity = initial_capacity ? initial_capacity : 1;
    result->items = malloc(result->capacity * sizeof *result->items);
    return result;
}

void leaf_values_push(leaf_values* lv, int item) {
    if (lv->size == lv->capacity) {
        size_t new_capacity = lv->capacity * 2;
        lv->items = realloc(lv->items, new_capacity * sizeof *lv->items);
        lv->capacity = new_capacity;
    }
    lv->items[lv->size++] = item;
}

void leaf_values_destroy(leaf_values* lv) {
    if (lv) {
        free(lv->items);
        free(lv);
    }
}

///// END OF MY OWN DYNAMIC ARRAY aka LIST!