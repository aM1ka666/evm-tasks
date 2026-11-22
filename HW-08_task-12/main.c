#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "task12.h"

int main(int argc, char **argv) {
    size_t length = 100000;
    Record *array;
    Record *reference;
    SortKey key = FIRST_KEY;
    int (*compare)(const void *, const void *);
    clock_t radix_start;
    clock_t radix_end;
    clock_t qsort_start;
    clock_t qsort_end;
    int keys_match = 1;
    int records_match = 1;
    int stable;

    if (argc > 3) {
        fprintf(stderr, "Usage: %s [positive array length] [key: 1 or 2]\n",
                argv[0]);
        return EXIT_FAILURE;
    }
    if (argc >= 2) {
        char *end;
        long value;

        errno = 0;
        value = strtol(argv[1], &end, 10);
        if (errno == ERANGE || end == argv[1] || *end != '\0' ||
            value <= 0 || (uintmax_t)value > SIZE_MAX / sizeof(*array)) {
            fprintf(stderr, "Invalid array length\n");
            return EXIT_FAILURE;
        }
        length = (size_t)value;
    }
    if (argc == 3) {
        if (strcmp(argv[2], "2") == 0) {
            key = SECOND_KEY;
        } else if (strcmp(argv[2], "1") != 0) {
            fprintf(stderr, "Invalid key. Use 1 or 2\n");
            return EXIT_FAILURE;
        }
    }
    compare = key == FIRST_KEY ? compare_first_key : compare_second_key;

    srand(1);
    array = generate_array(length);
    reference = malloc(length * sizeof(*reference));
    if (array == NULL || reference == NULL) {
        fprintf(stderr, "Not enough memory\n");
        free(array);
        free(reference);
        return EXIT_FAILURE;
    }
    memcpy(reference, array, length * sizeof(*array));

    printf("Sort key: %d\n", key == FIRST_KEY ? 1 : 2);
    if (length <= 20) {
        printf("Records: (field 1, field 2, original position)\n");
        printf("Original: ");
        print_array(array, length);
    }

    radix_start = clock();
    if (!radix_sort(array, length, key)) {
        fprintf(stderr, "Not enough memory\n");
        free(array);
        free(reference);
        return EXIT_FAILURE;
    }
    radix_end = clock();

    qsort_start = clock();
    qsort(reference, length, sizeof(*reference), compare);
    qsort_end = clock();

    for (size_t i = 0; i < length; i++) {
        if (array[i].keys[key] != reference[i].keys[key]) {
            keys_match = 0;
        }
        if (array[i].original_position != reference[i].original_position) {
            records_match = 0;
        }
    }

    if (length <= 20) {
        printf("Radix:    ");
        print_array(array, length);
        printf("qsort:    ");
        print_array(reference, length);
    }
    stable = is_stably_sorted(array, length, key);
    printf("Array length: %zu\n", length);
    printf("Keys match: %s\n", keys_match ? "yes" : "no");
    printf("Radix result is sorted and stable: %s\n", stable ? "yes" : "no");
    printf("qsort kept equal keys in order on this input: %s\n",
           is_stably_sorted(reference, length, key) ? "yes" : "no");
    printf("Record order matches: %s\n", records_match ? "yes" : "no");
    if (radix_start != (clock_t)-1 && radix_end != (clock_t)-1 &&
        qsort_start != (clock_t)-1 && qsort_end != (clock_t)-1) {
        printf("Radix sort: %.6f s\n",
               ((double)radix_end - radix_start) / CLOCKS_PER_SEC);
        printf("qsort:      %.6f s\n",
               ((double)qsort_end - qsort_start) / CLOCKS_PER_SEC);
    }

    free(array);
    free(reference);
    return keys_match && stable ? EXIT_SUCCESS : EXIT_FAILURE;
}

int compare_first_key(const void *left, const void *right) {
    const Record *a = left;
    const Record *b = right;

    return (a->keys[FIRST_KEY] > b->keys[FIRST_KEY]) -
           (a->keys[FIRST_KEY] < b->keys[FIRST_KEY]);
}

int compare_second_key(const void *left, const void *right) {
    const Record *a = left;
    const Record *b = right;

    return (a->keys[SECOND_KEY] > b->keys[SECOND_KEY]) -
           (a->keys[SECOND_KEY] < b->keys[SECOND_KEY]);
}

int is_stably_sorted(const Record *array, size_t length, SortKey key) {
    for (size_t i = 1; i < length; i++) {
        int previous = array[i - 1].keys[key];
        int current = array[i].keys[key];

        if (previous > current ||
            (previous == current &&
             array[i - 1].original_position >= array[i].original_position)) {
            return 0;
        }
    }
    return 1;
}

void print_array(const Record *array, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("(%d, %d, %zu) ", array[i].keys[FIRST_KEY],
               array[i].keys[SECOND_KEY], array[i].original_position);
    }
    printf("\n");
}
