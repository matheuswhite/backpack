/**
 * @file del_element.cpp
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief
 * @version 0.1
 * @date 26/09/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <gtest/gtest.h>
#include "bp_array.h"

TEST(DelElement, FirstElement)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    int err;

    err = bp_array_del(&array, 0);

    EXPECT_EQ(err, 0);
    for (int i = 0; i < 9; ++i) {
        EXPECT_EQ(buffer[i], i + 2);
    }
    EXPECT_EQ(array._size, 9);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(DelElement, LastElement)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    int err;

    err = bp_array_del(&array, 0);

    EXPECT_EQ(err, 0);
    for (int i = 0; i < 9; ++i) {
        EXPECT_EQ(buffer[i], i + 2);
    }
    EXPECT_EQ(array._size, 9);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(DelElement, WithOutOfRangeAtCapacityInFullArray)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    int err;

    err = bp_array_del(&array, 10);

    EXPECT_EQ(err, -EFAULT);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(buffer[i], i + 1);
    }
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(DelElement, WithOutOfRangeIndexInNonFullArray)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 9);
    int err;

    err = bp_array_del(&array, 9);

    EXPECT_EQ(err, -EFAULT);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(buffer[i], i + 1);
    }
    EXPECT_EQ(array._size, 9);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(DelElement, WithOutOfRangeAtCapacityInNonFullArray)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 9);
    int err;

    err = bp_array_del(&array, 10);

    EXPECT_EQ(err, -EFAULT);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(buffer[i], i + 1);
    }
    EXPECT_EQ(array._size, 9);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(DelElement, OnNullArray)
{
    int err;

    err = bp_array_del(nullptr, 0);

    EXPECT_EQ(err, -ENODEV);
}

TEST(DelElement, OnNotInitArray)
{
    uint16_t buffer[10] = {0};
    bp_array_t array    = {0};
    int err;

    err = bp_array_del(&array, 0);

    EXPECT_EQ(err, -EFAULT);
    EXPECT_EQ(buffer[0], 0);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 0);
    EXPECT_EQ(array._element_size, 0);
}

TEST(DelElement, OnEmptyArray)
{
    uint16_t buffer[10] = {0};
    bp_array_t array    = BP_ARRAY_INIT(buffer);
    int err;

    err = bp_array_del(&array, 0);

    EXPECT_EQ(err, -EFAULT);
    EXPECT_EQ(buffer[0], 0);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(DelElement, OnOneElementArray)
{
    uint16_t buffer[10] = {0};
    buffer[0]           = 1;
    bp_array_t array    = BP_ARRAY_START(buffer, 1);
    int err;

    err = bp_array_del(&array, 0);

    EXPECT_EQ(err, 0);
    EXPECT_EQ(buffer[0], 0);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}
