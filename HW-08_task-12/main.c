#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "task12.h"

int main(int argc, char **argv) {
    size_t length = 100000;
    int *array;
    int *reference;
    clock_t radix_start;
    clock_t radix_end;
    clock_t qsort_start;
    clock_t qsort_end;
    int matches = 1;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [positive array length]\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (argc == 2) {
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

    if (length <= 20) {
        printf("Original: ");
        print_array(array, length);
    }

    radix_start = clock();
    if (!radix_sort(array, length)) {
        fprintf(stderr, "Not enough memory\n");
        free(array);
        free(reference);
        return EXIT_FAILURE;
    }
    radix_end = clock();

    qsort_start = clock();
    qsort(reference, length, sizeof(*reference), compare_ints);
    qsort_end = clock();

    for (size_t i = 0; i < length; i++) {
        if (array[i] != reference[i]) {
            matches = 0;
            break;
        }
    }

    if (length <= 20) {
        printf("Sorted:   ");
        print_array(array, length);
    }
    printf("Array length: %zu\n", length);
    printf("Results match: %s\n", matches ? "yes" : "no");
    if (radix_start != (clock_t)-1 && radix_end != (clock_t)-1 &&
        qsort_start != (clock_t)-1 && qsort_end != (clock_t)-1) {
        printf("Radix sort: %.6f s\n",
               ((double)radix_end - radix_start) / CLOCKS_PER_SEC);
        printf("qsort:      %.6f s\n",
               ((double)qsort_end - qsort_start) / CLOCKS_PER_SEC);
    }

    free(array);
    free(reference);
    return matches ? EXIT_SUCCESS : EXIT_FAILURE;
}

int compare_ints(const void *left, const void *right) {
    int a = *(const int *)left;
    int b = *(const int *)right;

    return (a > b) - (a < b);
}

void print_array(const int *array, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
