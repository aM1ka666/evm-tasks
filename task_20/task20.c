#include "task20.h"
#include <stdlib.h>

int task20(int *a, int n) {
    if (n <= 0) {
        return 0;
    }

    int min_val = a[0];
    int max_val = a[0];

    for (int i = 1; i < n; i++) {
        if (a[i] < min_val) {
            min_val = a[i];
        }
        if (a[i] > max_val) {
            max_val = a[i];
        }
    }

    long long range = (long long)max_val - (long long)min_val + 1;
    int *seen = (int *)calloc((size_t)range, sizeof(int));
    
    if (seen == NULL) {
        return -1;
    }

    int write_idx = 0;
    for (int i = 0; i < n; i++) {
        long long idx = (long long)a[i] - (long long)min_val;
        if (seen[idx] == 0) {
            seen[idx] = 1;
            a[write_idx] = a[i];
            write_idx++;
        }
    }

    free(seen);
    return write_idx;
}