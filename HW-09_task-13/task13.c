#include <stdlib.h>
#include "task13.h"

int task13(int *array, size_t *length, int threshold) {
    size_t *indices;
    size_t count = 0;
    size_t remove_count = 0;
    size_t next_removal = 0;
    size_t write = 0;

    if (*length < 2) {
        return 1;
    }
    indices = calloc(*length, sizeof(*indices));
    if (indices == NULL) {
        return 0;
    }
    for (size_t i = 0; i < *length; i++) {
        if (array[i] > threshold) {
            indices[count++] = i;
        }
    }

    if (count > 1) {
        int last = array[indices[count - 1]];

        for (size_t i = count - 1; i > 0; i--) {
            array[indices[i]] = array[indices[i - 1]];
        }
        array[indices[0]] = last;
    }

    /* Collect the deletions before changing any array positions. */
    for (size_t i = 0; i < count; i++) {
        size_t j = indices[i];

        if (j >= 2 && array[j] == array[j - 2]) {
            indices[remove_count++] = j;
        }
    }
    for (size_t read = 0; read < *length; read++) {
        if (next_removal < remove_count && read == indices[next_removal]) {
            next_removal++;
        } else {
            array[write++] = array[read];
        }
    }

    *length = write;
    free(indices);
    return 1;
}
