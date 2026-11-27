#ifndef HW_09_TASK_13_H
#define HW_09_TASK_13_H

#include <stdio.h>

int main(void);
int read_input(FILE *input, int **array, size_t *length, int *threshold);
void print_array(const int *array, size_t length);
int task13(int *array, size_t *length, int threshold);

#endif
