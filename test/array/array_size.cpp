/**
 * @file array_size.cpp
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

TEST(ArraySize, NullArray)
{
    size_t size;

    size = bp_array_size(nullptr);

    EXPECT_EQ(size, 0);
}

TEST(ArraySize, NotInitArray)
{
    bp_array_t array = {0};
    size_t size;

    size = bp_array_size(&array);

    EXPECT_EQ(size, 0);
    EXPECT_EQ(array._array, nullptr);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 0);
    EXPECT_EQ(array._element_size, 0);
}

TEST(ArraySize, EmptyArray)
{
    uint16_t buffer[10] = {0};
    bp_array_t array    = BP_ARRAY_INIT(buffer);
    size_t size;

    size = bp_array_size(&array);

    EXPECT_EQ(size, 0);
    EXPECT_EQ(array._array, (uint8_t *) buffer);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(buffer[i], 0);
    }
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(ArraySize, OneElementArray)
{
    uint16_t buffer[10] = {0};
    buffer[0]           = 1;
    bp_array_t array    = BP_ARRAY_START(buffer, 1);
    size_t size;

    size = bp_array_size(&array);

    EXPECT_EQ(size, 1);
    EXPECT_EQ(buffer[0], 1);
    for (int i = 1; i < 10; ++i) {
        EXPECT_EQ(buffer[i], 0);
    }
    EXPECT_EQ(array._size, 1);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(ArraySize, FullLastOneArray)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 9; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 9);
    size_t size;

    size = bp_array_size(&array);

    EXPECT_EQ(size, 9);
    for (int i = 0; i < 9; ++i) {
        EXPECT_EQ(buffer[i], i + 1);
    }
    EXPECT_EQ(buffer[9], 0);
    EXPECT_EQ(array._size, 9);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(ArraySize, FullArray)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    size_t size;

    size = bp_array_size(&array);

    EXPECT_EQ(size, 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(buffer[i], i + 1);
    }
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}
