#include <stdio.h>

int task(FILE *in, long long *res);

int main(void) {
    FILE *in;
    int err;
    long long res;

    in = fopen("1.txt", "r");
    err = task(in, &res);

    if (err == 0) {
        printf("Not file\n");
        return -1;
    }

    fclose(in);

    if (err == -1) {
        printf("Bad file\n");
    }
    if (err == -2) {
        printf("Empty file\n");
    }
    if (err == -3) {
        printf("Not enough elements\n");
    }
    if (err == 1) {
        printf("result=%lld\n", res);
    }

    return 0;
}

int task(FILE *in, long long *res) {
    long long cur, min_prev, max_diff = 0;
    long long count = 0;
    int err;

    *res = 0;

    if (in == NULL) {
        err = 0;
    } else {
        if (fscanf(in, "%lld", &cur) == 1) {
            min_prev = cur;
            count = 1;

            while (fscanf(in, "%lld", &cur) == 1) {
                long long diff = cur - min_prev;

                if (count == 1 || diff > max_diff) {
                    max_diff = diff;
                }
                if (cur < min_prev) {
                    min_prev = cur;
                }
                count++;
            }
        }

        if (!feof(in)) {
            err = -1;
        } else if (count == 0) {
            err = -2;
        } else if (count < 2) {
            err = -3;
        } else {
            *res = max_diff;
            err = 1;
        }
    }

    return err;
}