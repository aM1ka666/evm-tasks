#include "task20.h"
#include <stdlib.h>

int task20(int **array, int n) {
    int *a = *array;
    int min_val;
    int max_val;
    long long range;
    int *seen;
    int *resized;
    int write_idx = 0;

    if (n <= 0) {
        free(a);
        *array = NULL;
        return 0;
    }

    min_val = a[0];
    max_val = a[0];

    for (int i = 1; i < n; i++) {
        if (a[i] < min_val) {
            min_val = a[i];
        }
        if (a[i] > max_val) {
            max_val = a[i];
        }
    }

    range = (long long)max_val - (long long)min_val + 1;
    seen = (int *)calloc((size_t)range, sizeof(int));

    if (seen == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        long long idx = (long long)a[i] - (long long)min_val;
        if (seen[idx] == 0) {
            seen[idx] = 1;
            a[write_idx] = a[i];
            write_idx++;
        }
    }

    free(seen);
    if (write_idx < n) {
        resized = realloc(a, (size_t)write_idx * sizeof(*a));
        if (resized == NULL) {
            return -1;
        }
        *array = resized;
    }
    return write_idx;
}
