/**
 * @file test_array.cpp
 * @author Matheus T. dos Santos (matheus.santos@edge.ufal.br)
 * @brief
 * @version 0.1
 * @date 14/09/2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <gtest/gtest.h>
#include "bp_array.h"

TEST(CreateArray, SimpleTypeHighCapacity)
{
    uint16_t buffer[10] = {0};

    bp_array_t array = BP_ARRAY_INIT(buffer);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(CreateArray, SimpleTypeCapacityOne)
{
    uint16_t buffer[1] = {0};

    bp_array_t array = BP_ARRAY_INIT(buffer);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 1);
    EXPECT_EQ(array._element_size, 2);
}

TEST(CreateArray, SimpleTypeCapacityZero)
{
    uint16_t buffer[0] = {};

    bp_array_t array = BP_ARRAY_INIT(buffer);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 0);
    EXPECT_EQ(array._element_size, 2);
}

TEST(CreateArray, StringTypeHighCapacity)
{
    char *buffer[10] = {nullptr};

    bp_array_t array = BP_ARRAY_INIT(buffer);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, sizeof(char *));
}

TEST(CreateArray, StringTypeCapacityOne)
{
    char *buffer[1] = {nullptr};

    bp_array_t array = BP_ARRAY_INIT(buffer);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 1);
    EXPECT_EQ(array._element_size, sizeof(char *));
}

TEST(CreateArray, StringTypeCapacityZero)
{
    char *buffer[0] = {};

    bp_array_t array = BP_ARRAY_INIT(buffer);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 0);
    EXPECT_EQ(array._element_size, sizeof(char *));
}

TEST(CreateArray, ArrayTypeHighCapacity)
{
    uint16_t buffer[10][32] = {0};

    bp_array_t array = BP_ARRAY_INIT(buffer);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 64);
}

TEST(CreateArray, ArrayTypeCapacityOne)
{
    uint16_t buffer[1][32] = {0};

    bp_array_t array = BP_ARRAY_INIT(buffer);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 1);
    EXPECT_EQ(array._element_size, 64);
}

TEST(CreateArray, ArrayTypeCapacityZero)
{
    uint16_t buffer[0][32] = {};

    bp_array_t array = BP_ARRAY_INIT(buffer);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 0);
    EXPECT_EQ(array._element_size, 64);
}

TEST(CreateArray, StructTypeHighCapacity)
{
    struct {
        uint16_t x;
        uint16_t y;
    } buffer[10] = {0};

    bp_array_t array = BP_ARRAY_INIT(buffer);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 4);
}

TEST(CreateArray, StructTypeCapacityOne)
{
    struct {
        uint16_t x;
        uint16_t y;
    } buffer[1] = {0};

    bp_array_t array = BP_ARRAY_INIT(buffer);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 1);
    EXPECT_EQ(array._element_size, 4);
}

TEST(CreateArray, StructTypeCapacityZero)
{
    struct {
        uint16_t x;
        uint16_t y;
    } buffer[0] = {};

    bp_array_t array = BP_ARRAY_INIT(buffer);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 0);
    EXPECT_EQ(array._element_size, 4);
}
