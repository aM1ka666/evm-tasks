#include <stdio.h>
#include <stdlib.h>

int read_array_1(FILE *in, int **a, int *n);
int read_array_2(FILE *in, int **a, int *n);
void print_array(const int *a, int n);
int task12(int *a, int n);

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
    new_n = task12(a, n);
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

int task12(int *a, int n) {
    int write_idx = 0;
    int read_idx = 0;

    if (n <= 0) {
        return 0;
    }

    while (read_idx < n) {
        int start = read_idx;
        while (read_idx + 1 < n && a[read_idx + 1] > a[read_idx]) {
            read_idx++;
        }

        int len = read_idx - start + 1;
        if (len >= 2) {
            long long sum = 0;
            for (int i = start; i <= read_idx; i++) {
                sum += a[i];
            }
            a[write_idx] = (int)(sum / len);
            write_idx++;
        } else {
            a[write_idx] = a[start];
            write_idx++;
        }

        read_idx++;
    }

    return write_idx;
}