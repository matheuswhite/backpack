/**
 * @file find_element.cpp
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief
 * @version 0.1
 * @date 27/09/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <gtest/gtest.h>
#include "bp_array.h"

extern "C" {
typedef struct {
    uint16_t x;
    uint16_t y;
} pos_t;

bool cmp_uint16_elements(void *el, void *param)
{
    uint16_t *el_ptr    = (uint16_t *) el;
    uint16_t *param_ptr = (uint16_t *) param;

    return *el_ptr == *param_ptr;
}

bool cmp_y_field(void *el, void *param)
{
    pos_t *el_ptr       = (pos_t *) el;
    uint16_t *param_ptr = (uint16_t *) param;

    return el_ptr->y == *param_ptr;
}

bool cmp_norm(void *el, void *param)
{
    pos_t *el_ptr       = (pos_t *) el;
    uint16_t *param_ptr = (uint16_t *) param;

    uint16_t x_square = (el_ptr->x) * (el_ptr->x);
    uint16_t y_square = (el_ptr->y) * (el_ptr->y);

    return x_square + y_square == *param_ptr;
}
}

TEST(FindElementIndex, OnNullArray)
{
    uint16_t param = 0;
    size_t index;
    uint16_t *el;

    index = bp_array_find_idx(nullptr, &param, cmp_uint16_elements);
    el    = (uint16_t *) bp_array_find(nullptr, &param, cmp_uint16_elements);

    EXPECT_EQ(index, BP_ARRAY_INVALID_INDEX);
    EXPECT_EQ(el, nullptr);
}

TEST(FindElementIndex, OnEmptyArray)
{
    uint16_t buffer[10] = {0};
    bp_array_t array    = BP_ARRAY_INIT(buffer);
    uint16_t param      = 0;
    size_t index;
    uint16_t *el;

    index = bp_array_find_idx(&array, &param, cmp_uint16_elements);
    el    = (uint16_t *) bp_array_find(&array, &param, cmp_uint16_elements);

    EXPECT_EQ(index, BP_ARRAY_INVALID_INDEX);
    EXPECT_EQ(el, nullptr);
    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(FindElementIndex, OnFullArrayInFirstPosition)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    uint16_t param   = 1;
    size_t index;
    uint16_t *el;

    index = bp_array_find_idx(&array, &param, cmp_uint16_elements);
    el    = (uint16_t *) bp_array_find(&array, &param, cmp_uint16_elements);

    EXPECT_EQ(index, 0);
    EXPECT_EQ(*el, 1);
    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(FindElementIndex, OnFullArrayInLastPosition)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    uint16_t param   = 10;
    size_t index;
    uint16_t *el;

    index = bp_array_find_idx(&array, &param, cmp_uint16_elements);
    el    = (uint16_t *) bp_array_find(&array, &param, cmp_uint16_elements);

    EXPECT_EQ(index, 9);
    EXPECT_EQ(*el, 10);
    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(FindElementIndex, OnFullArrayInMiddle)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    uint16_t param   = 5;
    size_t index;
    uint16_t *el;

    index = bp_array_find_idx(&array, &param, cmp_uint16_elements);
    el    = (uint16_t *) bp_array_find(&array, &param, cmp_uint16_elements);

    EXPECT_EQ(index, 4);
    EXPECT_EQ(*el, 5);
    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(FindElementIndex, OnOneElementArray)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    uint16_t param   = 1;
    size_t index;
    uint16_t *el;

    index = bp_array_find_idx(&array, &param, cmp_uint16_elements);
    el    = (uint16_t *) bp_array_find(&array, &param, cmp_uint16_elements);

    EXPECT_EQ(index, 0);
    EXPECT_EQ(*el, 1);
    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(FindElementIndex, WithParamElementCompareFunction)
{
    pos_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i].x = i + 1;
        buffer[i].y = (i + 1) * (i + 1);
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    uint16_t param   = 25;
    size_t index;
    pos_t *el;

    index = bp_array_find_idx(&array, &param, cmp_y_field);
    el    = (pos_t *) bp_array_find(&array, &param, cmp_y_field);

    EXPECT_EQ(index, 4);
    EXPECT_EQ(el->x, buffer[4].x);
    EXPECT_EQ(el->y, buffer[4].y);
    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 4);
}

TEST(FindElementIndex, WithComplexCompareFunction)
{
    pos_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i].x = i + 1;
        buffer[i].y = i + 2;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    uint16_t param   = 25 + 36;
    size_t index;
    pos_t *el;

    index = bp_array_find_idx(&array, &param, cmp_norm);
    el    = (pos_t *) bp_array_find(&array, &param, cmp_norm);

    EXPECT_EQ(index, 4);
    EXPECT_EQ(el->x, buffer[4].x);
    EXPECT_EQ(el->y, buffer[4].y);
    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 4);
}

TEST(FindElementIndex, WithElementNotInArray)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    uint16_t param   = 20;
    size_t index;
    uint16_t *el;

    index = bp_array_find_idx(&array, &param, cmp_uint16_elements);
    el    = (uint16_t *) bp_array_find(&array, &param, cmp_uint16_elements);

    EXPECT_EQ(index, BP_ARRAY_INVALID_INDEX);
    EXPECT_EQ(el, nullptr);
    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(FindElementIndex, WithDuplicateElementInSequence)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    buffer[5]        = buffer[4];
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    uint16_t param   = 5;
    size_t index;
    uint16_t *el;

    index = bp_array_find_idx(&array, &param, cmp_uint16_elements);
    el    = (uint16_t *) bp_array_find(&array, &param, cmp_uint16_elements);

    EXPECT_EQ(index, 4);
    EXPECT_EQ(*el, 5);
    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(FindElementIndex, WithDuplicateElementNotInSequence)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    buffer[6]        = buffer[4];
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    uint16_t param   = 5;
    size_t index;
    uint16_t *el;

    index = bp_array_find_idx(&array, &param, cmp_uint16_elements);
    el    = (uint16_t *) bp_array_find(&array, &param, cmp_uint16_elements);

    EXPECT_EQ(index, 4);
    EXPECT_EQ(*el, 5);
    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}
