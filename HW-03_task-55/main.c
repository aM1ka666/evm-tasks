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
    if (err == 1) {
        printf("result=%lld\n", res);
    }

    return 0;
}

int task(FILE *in, long long *res) {
    long long cur;
    int state = -1;

    *res = 0;

    if (in == NULL) {
        return 0;
    }

    while (fscanf(in, "%lld", &cur) == 1) {
        if (state <= 0) {
            if (cur == 1) {
                state = 1;
            } else {
                state = 0;
            }
        } else if (state == 1) {
            if (cur == 2) {
                state = 2;
            } else if (cur != 1) {
                state = 0;
            }
        } else if (state == 2) {
            if (cur == 1) {
                state = 3;
            } else {
                state = 0;
            }
        } else if (state == 3) {
            if (cur == 0) {
                state = 4;
            } else if (cur == 2) {
                state = 2;
            } else if (cur == 1) {
                state = 1;
            } else {
                state = 0;
            }
        } else if (state == 4) {
            if (cur == 2) {
                (*res)++;
                state = 0;
            } else if (cur == 1) {
                state = 1;
            } else {
                state = 0;
            }
        }
    }

    if (!feof(in)) {
        return -1;
    }
    if (state == -1) {
        return -2;
    }

    return 1;
}
