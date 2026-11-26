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
    KeyFunction key = value_key;
    int (*compare)(const void *, const void *) = compare_values;
    clock_t counting_start;
    clock_t counting_end;
    clock_t qsort_start;
    clock_t qsort_end;
    int keys_match = 1;
    int values_match = 1;

    if (argc == 2 && strcmp(argv[1], "demo") == 0) {
        return demonstrate_stability();
    }
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
            key = last_digit_key;
            compare = compare_last_digits;
        } else if (strcmp(argv[2], "1") != 0) {
            fprintf(stderr, "Invalid key. Use 1 or 2\n");
            return EXIT_FAILURE;
        }
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

    printf("Sort key: %s\n", key == value_key ? "x" : "x % 10");
    if (length <= 20) {
        printf("Original: ");
        print_array(array, length);
    }

    counting_start = clock();
    if (!counting_sort(array, length, key)) {
        fprintf(stderr, "Not enough memory\n");
        free(array);
        free(reference);
        return EXIT_FAILURE;
    }
    counting_end = clock();

    qsort_start = clock();
    qsort(reference, length, sizeof(*reference), compare);
    qsort_end = clock();

    for (size_t i = 0; i < length; i++) {
        if (key(array[i]) != key(reference[i])) {
            keys_match = 0;
        }
        if (array[i] != reference[i]) {
            values_match = 0;
        }
    }

    if (length <= 20) {
        printf("Counting: ");
        print_array(array, length);
        printf("qsort:    ");
        print_array(reference, length);
    }
    printf("Array length: %zu\n", length);
    printf("Keys match: %s\n", keys_match ? "yes" : "no");
    printf("Order of values matches qsort: %s\n", values_match ? "yes" : "no");
    if (counting_start != (clock_t)-1 && counting_end != (clock_t)-1 &&
        qsort_start != (clock_t)-1 && qsort_end != (clock_t)-1) {
        printf("Counting sort: %.6f s\n",
               ((double)counting_end - counting_start) / CLOCKS_PER_SEC);
        printf("qsort:      %.6f s\n",
               ((double)qsort_end - qsort_start) / CLOCKS_PER_SEC);
    }

    free(array);
    free(reference);
    return keys_match ? EXIT_SUCCESS : EXIT_FAILURE;
}

int compare_keys(const void *left, const void *right, KeyFunction key) {
    int a = key(*(const int *)left);
    int b = key(*(const int *)right);

    return (a > b) - (a < b);
}

int compare_values(const void *left, const void *right) {
    return compare_keys(left, right, value_key);
}

int compare_last_digits(const void *left, const void *right) {
    return compare_keys(left, right, last_digit_key);
}

void print_array(const int *array, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int demonstrate_stability(void) {
    int array[] = {32, 27, 22, 17, 12, 7};
    size_t length = sizeof(array) / sizeof(*array);

    printf("Sort key: x %% 10\n");
    printf("Original: ");
    print_array(array, length);
    if (!counting_sort(array, length, last_digit_key)) {
        fprintf(stderr, "Not enough memory\n");
        return EXIT_FAILURE;
    }
    printf("Counting: ");
    print_array(array, length);
    return EXIT_SUCCESS;
}
