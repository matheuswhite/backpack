/**
 * @file get_element.cpp
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

TEST(GetElement, FirstElement)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    uint16_t *el_ptr;

    el_ptr = (uint16_t *) bp_array_get(&array, 0);

    EXPECT_EQ(*el_ptr, 1);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(GetElement, SecondElement)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    uint16_t *el_ptr;

    el_ptr = (uint16_t *) bp_array_get(&array, 1);

    EXPECT_EQ(*el_ptr, 2);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(GetElement, LastElementFullArray)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    uint16_t *el_ptr;

    el_ptr = (uint16_t *) bp_array_get(&array, 9);

    EXPECT_EQ(*el_ptr, 10);
    EXPECT_EQ(buffer[9], 10);
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(GetElement, LastElementNonFullArray)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 9);
    uint16_t *el_ptr;

    el_ptr = (uint16_t *) bp_array_get(&array, 8);

    EXPECT_EQ(*el_ptr, 9);
    EXPECT_EQ(buffer[8], 9);
    EXPECT_EQ(array._size, 9);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(GetElement, OnEmptyArray)
{
    uint16_t buffer[10] = {0};
    bp_array_t array    = BP_ARRAY_INIT(buffer);
    uint16_t *el_ptr;

    el_ptr = (uint16_t *) bp_array_get(&array, 0);

    EXPECT_EQ(el_ptr, nullptr);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(GetElement, WithOutOfRangeIndex)
{
    uint16_t buffer[10] = {0};
    bp_array_t array    = BP_ARRAY_START(buffer, 9);
    uint16_t *el_ptr;

    el_ptr = (uint16_t *) bp_array_get(&array, 9);

    EXPECT_EQ(el_ptr, nullptr);
    EXPECT_EQ(array._size, 9);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(GetElement, WithOutOfRangeAtCapacity)
{
    uint16_t buffer[10] = {0};
    bp_array_t array    = BP_ARRAY_START(buffer, 9);
    uint16_t *el_ptr;

    el_ptr = (uint16_t *) bp_array_get(&array, 10);

    EXPECT_EQ(el_ptr, nullptr);
    EXPECT_EQ(array._size, 9);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(GetElement, OnNullArray)
{
    uint16_t *el_ptr;

    el_ptr = (uint16_t *) bp_array_get(nullptr, 10);

    EXPECT_EQ(el_ptr, nullptr);
}

TEST(GetElement, OnNotInitArray)
{
    bp_array_t array = {0};
    uint16_t *el_ptr;

    el_ptr = (uint16_t *) bp_array_get(&array, 10);

    EXPECT_EQ(el_ptr, nullptr);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 0);
    EXPECT_EQ(array._element_size, 0);
}
