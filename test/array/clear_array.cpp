/**
 * @file clear_array.cpp
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

TEST(ClearArray, NullArray)
{
    int err;

    err = bp_array_clear(nullptr);

    EXPECT_EQ(err, -ENODEV);
}

TEST(ClearArray, NotInitArray)
{
    bp_array_t array = {0};
    int err;

    err = bp_array_clear(&array);

    EXPECT_EQ(err, 0);
    EXPECT_EQ(array._array, nullptr);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 0);
    EXPECT_EQ(array._element_size, 0);
}

TEST(ClearArray, EmptyArray)
{
    uint16_t buffer[10] = {0};
    bp_array_t array    = BP_ARRAY_INIT(buffer);
    int err;

    err = bp_array_clear(&array);

    EXPECT_EQ(err, 0);
    EXPECT_EQ(buffer[0], 0);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(ClearArray, OneElementArray)
{
    uint16_t buffer[10] = {0};
    buffer[0]           = 1;
    bp_array_t array    = BP_ARRAY_START(buffer, 1);
    int err;

    err = bp_array_clear(&array);

    EXPECT_EQ(err, 0);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(ClearArray, FullLastOneArray)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 9; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 9);
    int err;

    err = bp_array_clear(&array);

    EXPECT_EQ(err, 0);
    for (int i = 0; i < 9; ++i) {
        EXPECT_EQ(buffer[i], i + 1);
    }
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(ClearArray, FullArray)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    int err;

    err = bp_array_clear(&array);

    EXPECT_EQ(err, 0);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(buffer[i], i + 1);
    }
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}
