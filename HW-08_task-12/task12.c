#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "task12.h"

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

int counting_sort(int *array, size_t length, KeyFunction key) {
    int *buffer;
    size_t *next;
    int min_key;
    int max_key;
    uintmax_t span;
    size_t range;
    size_t offset = 0;

    if (length < 2) {
        return 1;
    }
    if (length > SIZE_MAX / sizeof(*array)) {
        return 0;
    }

    min_key = key(array[0]);
    max_key = min_key;
    for (size_t i = 1; i < length; i++) {
        int current_key = key(array[i]);
        if (current_key < min_key) {
            min_key = current_key;
        }
        if (current_key > max_key) {
            max_key = current_key;
        }
    }
    span = (uintmax_t)max_key - (uintmax_t)min_key;
    if (span >= SIZE_MAX / sizeof(*next)) {
        return 0;
    }
    range = (size_t)span + 1;

    next = calloc(range, sizeof(*next));
    buffer = malloc(length * sizeof(*buffer));
    if (next == NULL || buffer == NULL) {
        free(next);
        free(buffer);
        return 0;
    }

    for (size_t i = 0; i < length; i++) {
        unsigned int index = (unsigned int)key(array[i]) - (unsigned int)min_key;
        next[index]++;
    }
    for (size_t i = 0; i < range; i++) {
        size_t count = next[i];
        next[i] = offset;
        offset += count;
    }
    for (size_t i = 0; i < length; i++) {
        unsigned int index = (unsigned int)key(array[i]) - (unsigned int)min_key;
        buffer[next[index]++] = array[i];
    }

    memcpy(array, buffer, length * sizeof(*array));
    free(next);
    free(buffer);
    return 1;
}
