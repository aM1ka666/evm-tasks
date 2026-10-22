#include <stdio.h>
#include <stdlib.h>

int read_array_1(FILE *in, int **a, int *n);
int read_array_2(FILE *in, int **a, int *n);
void print_array(const int *a, int n);
int task38(const int *a, int n, int *res_k);

int main(void) {
    FILE *in;
    int *a = NULL;
    int n = 0;
    int err;
    int res_k;
    int found;

    in = fopen("1.txt", "r");
    if (in == NULL) {
        printf("Not file\n");
        return -1;
    }

    err = read_array_2(in, &a, &n);
    fclose(in);

    if (err == -1) {
        printf("Bad file\n");
        return -1;
    }
    if (err == -2) {
        printf("Empty file\n");
        return -1;
    }

    print_array(a, n);
    found = task38(a, n, &res_k);

    if (found) {
        printf("result=%d\n", res_k);
    } else {
        printf("No such k\n");
    }

    free(a);
    return 0;
}

int read_array_1(FILE *in, int **a, int *n) {
    int total;
    int dummy;

    if (fscanf(in, "%d", &total) != 1) {
        if (feof(in)) {
            return -2;
        }
        return -1;
    }

    if (total <= 0) {
        return -1;
    }

    *a = (int *)malloc((size_t)total * sizeof(int));
    if (*a == NULL) {
        return -1;
    }

    for (int i = 0; i < total; i++) {
        if (fscanf(in, "%d", &((*a)[i])) != 1) {
            free(*a);
            *a = NULL;
            return -1;
        }
    }

    if (fscanf(in, "%d", &dummy) == 1) {
        free(*a);
        *a = NULL;
        return -1;
    }
    if (!feof(in)) {
        free(*a);
        *a = NULL;
        return -1;
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

int task38(const int *a, int n, int *res_k) {
    long long total_sum = 0;
    long long sum_less_k = 0;
    int cur_v;
    int k = 1;

    if (n <= 0) {
        return 0;
    }

    cur_v = a[0];
    for (int i = 0; i < n; i++) {
        total_sum += a[i];
        if (a[i] > cur_v) {
            cur_v = a[i];
        }
    }

    while (1) {
        long long sum_vk = 0;
        int has_next = 0;
        int next_v = 0;
        long long s_le;
        long long s_ge;
        long long abs_le;
        long long abs_ge;

        for (int i = 0; i < n; i++) {
            if (a[i] == cur_v) {
                sum_vk += a[i];
            } else if (a[i] < cur_v) {
                if (!has_next || a[i] > next_v) {
                    next_v = a[i];
                    has_next = 1;
                }
            }
        }

        s_le = sum_less_k + sum_vk;
        s_ge = total_sum - sum_less_k;

        abs_le = (s_le < 0) ? -s_le : s_le;
        abs_ge = (s_ge < 0) ? -s_ge : s_ge;

        if (abs_le == abs_ge) {
            *res_k = k;
            return 1;
        }

        if (!has_next) {
            break;
        }

        sum_less_k = s_le;
        cur_v = next_v;
        k++;
    }

    return 0;
}