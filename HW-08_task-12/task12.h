#ifndef HW_08_TASK_12_H
#define HW_08_TASK_12_H

#include <stddef.h>

typedef int (*KeyFunction)(int);

int main(int argc, char **argv);
int *generate_array(size_t length);
int value_key(int value);
int last_digit_key(int value);
int radix_sort(int *array, size_t length, KeyFunction key);
int compare_keys(const void *left, const void *right, KeyFunction key);
int compare_values(const void *left, const void *right);
int compare_last_digits(const void *left, const void *right);
void print_array(const int *array, size_t length);
int demonstrate_stability(void);

#endif
