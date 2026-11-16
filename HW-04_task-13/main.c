#include <stdio.h>

int read_array_1(FILE *in, int *a, int *n);
int read_array_2(FILE *in, int *a, int *n);
void print_array(const int *a, int n);
int task13(int *a, int n);

int main(void) {
    FILE *in;
    int a[1000];
    int n = 0;
    int err;

    in = fopen("1.txt", "r");
    if (in == NULL) {
        printf("Not file\n");
        return -1;
    }

    err = read_array_2(in, a, &n);
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
    task13(a, n);
    print_array(a, n);

    return 0;
}

int read_array_1(FILE *in, int *a, int *n) {
    int total;
    int dummy;

    if (fscanf(in, "%d", &total) != 1) {
        if (feof(in)) {
            return -2;
        }
        return -1;
    }

    if (total <= 0 || total > 1000) {
        return -1;
    }

    for (int i = 0; i < total; i++) {
        if (fscanf(in, "%d", &a[i]) != 1) {
            return -1;
        }
    }

    if (fscanf(in, "%d", &dummy) == 1) {
        return -1;
    }
    if (!feof(in)) {
        return -1;
    }

    *n = total;
    return 1;
}

int read_array_2(FILE *in, int *a, int *n) {
    int count = 0;
    int val;

    while (count < 1000 && fscanf(in, "%d", &val) == 1) {
        a[count] = val;
        count++;
    }

    if (!feof(in)) {
        return -1;
    }
    if (count == 0) {
        return -2;
    }

    *n = count;
    return 1;
}

void print_array(const int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int task13(int *a, int n) {
    int count = 0;
    int dest = 0;
    int val0;
    int len0;
    int hole_len;
    int src;

    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && a[j] == a[i]) {
            j++;
        }
        if (j - i >= 2) {
            count++;
        }
        i = j;
    }

    if (count <= 1) {
        return 1;
    }

    while (dest < n) {
        int j = dest;
        while (j < n && a[j] == a[dest]) {
            j++;
        }
        if (j - dest >= 2) {
            break;
        }
        dest = j;
    }

    val0 = a[dest];
    {
        int j0 = dest;
        while (j0 < n && a[j0] == val0) {
            j0++;
        }
        len0 = j0 - dest;
    }

    hole_len = len0;
    src = dest + hole_len;

    for (int k = 1; k < count; k++) {
        int s_start = src;
        int s_val;
        int s_end;
        int s_len;
        int g_len;
        int orig_g;
        int new_g;

        while (s_start < n) {
            int j = s_start;
            while (j < n && a[j] == a[s_start]) {
                j++;
            }
            if (j - s_start >= 2) {
                break;
            }
            s_start = j;
        }

        s_val = a[s_start];
        s_end = s_start;
        while (s_end < n && a[s_end] == s_val) {
            s_end++;
        }
        s_len = s_end - s_start;

        g_len = s_start - src;
        orig_g = src;
        new_g = dest + s_len;

        if (g_len > 0) {
            if (new_g < orig_g) {
                for (int i = 0; i < g_len; i++) {
                    a[new_g + i] = a[orig_g + i];
                }
            } else if (new_g > orig_g) {
                for (int i = g_len - 1; i >= 0; i--) {
                    a[new_g + i] = a[orig_g + i];
                }
            }
        }

        for (int i = 0; i < s_len; i++) {
            a[dest + i] = s_val;
        }

        dest = new_g + g_len;
        src = dest + hole_len;
    }

    for (int i = 0; i < len0; i++) {
        a[dest + i] = val0;
    }

    return 1;
}