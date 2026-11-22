#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "task12.h"

#define RADIX 256

int *generate_array(size_t length) {
    int *array;

    if (length > SIZE_MAX / sizeof(*array)) {
        return NULL;
    }
    array = malloc(length * sizeof(*array));
    if (array != NULL) {
        for (size_t i = 0; i < length; i++) {
            array[i] = rand() % 2001 - 1000;
        }
    }
    return array;
}

int value_key(int value) {
    return value;
}

int last_digit_key(int value) {
    return value % 10;
}

int radix_sort(int *array, size_t length, KeyFunction key) {
    int *buffer;
    unsigned int shift = 0;

    if (length < 2) {
        return 1;
    }
    if (length > SIZE_MAX / sizeof(*array)) {
        return 0;
    }
    buffer = malloc(length * sizeof(*buffer));
    if (buffer == NULL) {
        return 0;
    }

    for (unsigned int remaining = UINT_MAX; remaining != 0; remaining >>= 8) {
        size_t next[RADIX] = {0};
        size_t offset = 0;

        for (size_t i = 0; i < length; i++) {
            unsigned int ordered_key = (unsigned int)key(array[i]) -
                                       (unsigned int)INT_MIN;
            unsigned int digit = (ordered_key >> shift) & (RADIX - 1);
            next[digit]++;
        }

        for (size_t digit = 0; digit < RADIX; digit++) {
            size_t count = next[digit];
            next[digit] = offset;
            offset += count;
        }

        for (size_t i = 0; i < length; i++) {
            unsigned int ordered_key = (unsigned int)key(array[i]) -
                                       (unsigned int)INT_MIN;
            unsigned int digit = (ordered_key >> shift) & (RADIX - 1);
            buffer[next[digit]++] = array[i];
        }

        memcpy(array, buffer, length * sizeof(*array));
        shift += 8;
    }

    free(buffer);
    return 1;
}
