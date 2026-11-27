#include <stdlib.h>
#include "task13.h"

int main(void) {
    FILE *input;
    int *array = NULL;
    size_t length = 0;
    int threshold;

    input = fopen("1.txt", "r");
    if (input == NULL) {
        fprintf(stderr, "Cannot open 1.txt\n");
        return EXIT_FAILURE;
    }

    if (!read_input(input, &array, &length, &threshold)) {
        fprintf(stderr, "Cannot read input: expected n, M and n integers\n");
        fclose(input);
        free(array);
        return EXIT_FAILURE;
    }
    fclose(input);

    printf("Before: ");
    print_array(array, length);
    if (!task13(array, &length, threshold)) {
        fprintf(stderr, "Cannot allocate the index array\n");
        free(array);
        return EXIT_FAILURE;
    }
    printf("After:  ");
    print_array(array, length);
    printf("Length: %zu\n", length);
    free(array);
    return EXIT_SUCCESS;
}

int read_input(FILE *input, int **array, size_t *length, int *threshold) {
    int n;
    char extra;

    if (fscanf(input, "%d%d", &n, threshold) != 2 || n < 0) {
        return 0;
    }
    *length = (size_t)n;
    if (*length != 0) {
        *array = calloc(*length, sizeof(**array));
        if (*array == NULL) {
            return 0;
        }
    }

    for (size_t i = 0; i < *length; i++) {
        if (fscanf(input, "%d", &(*array)[i]) != 1) {
            return 0;
        }
    }
    return fscanf(input, " %c", &extra) == EOF && feof(input);
}

void print_array(const int *array, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", array[i]);
    }
    puts("");
}
