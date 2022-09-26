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

TEST(StartArray, SimpleTypeEmpty)
{
    uint16_t buffer[10] = {0};

    bp_array_t array = BP_ARRAY_START(buffer, 0);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(StartArray, SimpleTypeOneElement)
{
    uint16_t buffer[10] = {0};

    bp_array_t array = BP_ARRAY_START(buffer, 1);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 1);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(StartArray, SimpleTypeFull)
{
    uint16_t buffer[10] = {0};

    bp_array_t array = BP_ARRAY_START(buffer, 10);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(StartArray, SimpleTypeFullLastOne)
{
    uint16_t buffer[10] = {0};

    bp_array_t array = BP_ARRAY_START(buffer, 9);

    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 9);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}
