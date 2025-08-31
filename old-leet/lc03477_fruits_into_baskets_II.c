#include "a_leetcode.h"

// https://leetcode.com/problems/fruits-into-baskets-ii/description/?envType=daily-question&envId=2025-08-05

bool is_placed(int fruit_count, int* baskets, bool* used_baskets, int baskets_size) {
    bool placed = false;
    for (int j = 0; j < baskets_size; j++) {
        const bool is_unused_and_has_enough_capacity = 
            !used_baskets[j] && baskets[j] >= fruit_count;

        if (is_unused_and_has_enough_capacity) {
            used_baskets[j] = true;
            placed = true;
            break;
        }
    }
    return placed;
}

bool* used_baskets_create(int baskets_size) {
    bool* used_baskets = malloc((sizeof *used_baskets) * baskets_size);

    for (int i = 0; i < baskets_size; i++) {
        used_baskets[i] = false;
    }
    return used_baskets;
}

void used_baskets_destroy(bool* used_baskets) {
    if (used_baskets) free(used_baskets);
}


int numOfUnplacedFruits(int* fruits, int fruits_size, int* baskets, int baskets_size) {
    bool* used_baskets = used_baskets_create(baskets_size);
    int unplaced_count = 0;

    for (int i = 0; i < fruits_size; i++) {
        if (!is_placed(fruits[i], baskets, used_baskets, baskets_size)) {
            unplaced_count++;
        }
    }

    used_baskets_destroy(used_baskets);

    return unplaced_count;
}

