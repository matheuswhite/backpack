/*!
 * @file array.c
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 09/12/2021
 *
 * @copyright Matheus T. dos Santos all rights reserved (c) 2021
 *
 */
#include <stdio.h>
#include "bp_array.h"

int global_data[10]     = {0};
bp_array_t global_array = BP_ARRAY_INIT(global_data);

struct test {
    int data_inside_struct[6];
    bp_array_t array_inside_struct;
};

struct test test1 = {
    .data_inside_struct  = {0},
    .array_inside_struct = BP_ARRAY_INIT(test1.data_inside_struct),
};

struct key_value {
    int key;
    int value;
};

bool find_in_key_value(void *el, void *param)
{
    int *key                = param;
    struct key_value *el_kv = el;

    return *key == el_kv->key;
}

int main(void)
{
    int *ptr;
    int data;
    int key;
    struct key_value *kv1;
    size_t kv1_index;
    int local_data[11]              = {0};
    int data_with_values[5]         = {1, 2, 3, 4, 0};
    struct key_value struct_data[3] = {
        {
            .key   = 5,
            .value = 21,
        },
        {
            .key   = 4,
            .value = 11,
        },
        {
            .key   = 3,
            .value = 37,
        },
    };
    bp_array_t array1 = BP_ARRAY_INIT(local_data);
    bp_array_t array2 = BP_ARRAY_START(data_with_values, 4);
    bp_array_t array3 = BP_ARRAY_START(struct_data, 3);

    /* Get the 2nd element of array2 */
    ptr = bp_array_get(&array2, 1);
    printf("The 2nd element in array2 is: %d\n", *ptr);

    /* Pushing an element into array1. */
    printf("Array1 has %lu items before the 'push'\n", bp_array_size(&array1));
    data = 42;
    bp_array_push(&array1, &data);
    printf("Array1 has %lu items after the 'push'\n", bp_array_size(&array1));

    /* Delete the 1st element in array3. */
    printf("Array3 has %lu items before the 'delete'\n", bp_array_size(&array3));
    bp_array_del(&array3, 0);
    printf("Array3 has %lu items after the 'delete'\n", bp_array_size(&array3));

    /* Find the element with key 3 and its index */
    key       = 3;
    kv1       = bp_array_find(&array3, &key, find_in_key_value);
    kv1_index = bp_array_find_idx(&array3, &key, find_in_key_value);
    if (kv1_index == BP_ARRAY_INVALID_INDEX) {
        printf("Cannot find the index of an element with key %d in the array3\n", key);
        return -1;
    }
    printf("The value of the element, with key '%d', is: %d. And its index is: %lu\n",
           key, kv1->value, kv1_index);

    /* Clear the array2 */
    printf("The size of the array2 before the 'clear' is: %lu\n", bp_array_size(&array2));
    bp_array_clear(&array2);
    printf("The size of the array2 after the 'clear' is: %lu\n", bp_array_size(&array2));

    return 0;
}
