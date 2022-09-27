/**
 * @file array_iter.cpp
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
#include "bp_iter.h"

TEST(ArrayIter, FullArray)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    int i            = 0;
    bp_iter_t it;

    it = bp_array_iter(&array);

    BP_FOREACH(uint16_t, el, &it)
    {
        EXPECT_EQ(buffer[i], *el);
        i++;
    }
    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(ArrayIter, EmptyArray)
{
    uint16_t buffer[10] = {0};
    bp_array_t array    = BP_ARRAY_INIT(buffer);
    bp_iter_t it;

    it = bp_array_iter(&array);

    EXPECT_EQ(it.init(&it), nullptr);
    EXPECT_EQ(it.next(&it), false);
    EXPECT_EQ(it.get(&it), nullptr);
    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(ArrayIter, NullArray)
{
    bp_iter_t it;

    it = bp_array_iter(nullptr);

    EXPECT_EQ(it.init(&it), nullptr);
    EXPECT_EQ(it.next(&it), false);
    EXPECT_EQ(it.get(&it), nullptr);
}

TEST(ArrayIter, NotInitArray)
{
    bp_array_t array = {0};
    bp_iter_t it;

    it = bp_array_iter(&array);

    EXPECT_EQ(it.init(&it), nullptr);
    EXPECT_EQ(it.next(&it), false);
    EXPECT_EQ(it.get(&it), nullptr);
    EXPECT_EQ(array._array, nullptr);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 0);
    EXPECT_EQ(array._element_size, 0);
}

TEST(ArrayIter, FullLastOneArray)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 9);
    int i            = 0;
    bp_iter_t it;

    it = bp_array_iter(&array);

    BP_FOREACH(uint16_t, el, &it)
    {
        EXPECT_EQ(buffer[i], *el);
        i++;
    }
    EXPECT_EQ(i, 9);
    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 9);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(ArrayIter, OneElementArray)
{
    uint16_t buffer[10] = {0};
    buffer[0]           = 1;
    bp_array_t array    = BP_ARRAY_START(buffer, 1);
    int i               = 0;
    bp_iter_t it;

    it = bp_array_iter(&array);

    BP_FOREACH(uint16_t, el, &it)
    {
        EXPECT_EQ(buffer[i], *el);
        i++;
    }
    EXPECT_EQ(i, 1);
    EXPECT_EQ(array._array, (uint8_t *) buffer);
    EXPECT_EQ(array._size, 1);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}
