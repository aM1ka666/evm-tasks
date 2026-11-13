#include <stdlib.h>
#include "task20.h"

int main(void) {
    FILE *in;
    int *a = NULL;
    int n = 0;
    int err;
    int new_n;

    in = fopen("1.txt", "r");
    if (in == NULL) {
        printf("Not file\n");
        return -1;
    }

    err = read_array_1(in, &a, &n);
    fclose(in);

    if (err == -1) {
        printf("Bad file\n");
        return -1;
    }
    if (err == -2) {
        printf("Empty file\n");
        return -1;
    }
    if (err == -3) {
        printf("Not enough elements\n");
        return -1;
    }
    if (err == -4) {
        printf("Too many elements\n");
        return -1;
    }

    print_array(a, n);
    new_n = task20(&a, n);

    if (new_n < 0) {
        fprintf(stderr, "Not enough memory\n");
        free(a);
        return EXIT_FAILURE;
    }

    print_array(a, new_n);
    free(a);
    return 0;
}

int read_array_1(FILE *in, int **a, int *n) {
    int total;
    int val;
    int count = 0;
    int extra_count = 0;

    if (fscanf(in, "%d", &total) != 1) {
        if (feof(in)) {
            return -2;
        }
        return -1;
    }

    if (total == 0) {
        while (fscanf(in, "%d", &val) == 1) {
            extra_count++;
        }
        if (!feof(in)) {
            return -1;
        }
        if (extra_count > 0) {
            return -4;
        }
        return -2;
    }

    if (total < 0) {
        while (fscanf(in, "%d", &val) == 1) {
        }
        if (!feof(in)) {
            return -1;
        }
        return -1;
    }

    *a = (int *)malloc((size_t)total * sizeof(int));
    if (*a == NULL) {
        return -1;
    }

    while (count < total && fscanf(in, "%d", &val) == 1) {
        (*a)[count] = val;
        count++;
    }

    if (count < total) {
        free(*a);
        *a = NULL;
        if (!feof(in)) {
            return -1;
        }
        return -3;
    }

    while (fscanf(in, "%d", &val) == 1) {
        extra_count++;
    }

    if (!feof(in)) {
        free(*a);
        *a = NULL;
        return -1;
    }

    if (extra_count > 0) {
        free(*a);
        *a = NULL;
        return -4;
    }

    *n = total;
    return 1;
}

int read_array_2(FILE *in, int **a, int *n) {
    int count = 0;
    int cap = 16;
    int val;
    int *buf;

    buf = (int *)malloc((size_t)cap * sizeof(int));
    if (buf == NULL) {
        return -1;
    }

    while (fscanf(in, "%d", &val) == 1) {
        if (count >= cap) {
            int new_cap = cap * 2;
            int *new_buf = (int *)realloc(buf, (size_t)new_cap * sizeof(int));
            if (new_buf == NULL) {
                free(buf);
                return -1;
            }
            buf = new_buf;
            cap = new_cap;
        }
        buf[count] = val;
        count++;
    }

    if (!feof(in)) {
        free(buf);
        return -1;
    }
    if (count == 0) {
        free(buf);
        return -2;
    }

    *a = buf;
    *n = count;
    return 1;
}

void print_array(const int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
