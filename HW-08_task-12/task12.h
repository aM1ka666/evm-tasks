#ifndef HW_08_TASK_12_H
#define HW_08_TASK_12_H

#include <stddef.h>

int main(int argc, char **argv);
int *generate_array(size_t length);
int radix_sort(int *array, size_t length);
int compare_ints(const void *left, const void *right);
void print_array(const int *array, size_t length);

#endif
