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
    long long cur;
    long long i = 0;
    long long ok = 1;

    *res = 0;

    if (in == NULL) {
        return 0;
    }

    while (fscanf(in, "%lld", &cur) == 1) {
        i++;
        if (cur != i) {
            ok = 0;
        }
    }

    if (!feof(in)) {
        return -1;
    }
    if (i == 0) {
        return -2;
    }

    *res = ok;
    return 1;
}
