#ifndef HW_08_TASK_12_H
#define HW_08_TASK_12_H

#include <stddef.h>

typedef enum { FIRST_KEY, SECOND_KEY } SortKey;

typedef struct {
    int keys[2];
    size_t original_position;
} Record;

int main(int argc, char **argv);
Record *generate_array(size_t length);
int radix_sort(Record *array, size_t length, SortKey key);
int compare_first_key(const void *left, const void *right);
int compare_second_key(const void *left, const void *right);
int is_stably_sorted(const Record *array, size_t length, SortKey key);
void print_array(const Record *array, size_t length);

#endif
