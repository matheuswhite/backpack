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

TEST(PushElement, NullElement)
{
    uint16_t buffer[10] = {0};
    bp_array_t array    = BP_ARRAY_INIT(buffer);
    int err;

    err = bp_array_push(&array, nullptr);

    EXPECT_EQ(err, -ENODEV);
    EXPECT_EQ(buffer[0], 0);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(PushElement, StringElement)
{
    char *buffer[10] = {nullptr};
    bp_array_t array = BP_ARRAY_INIT(buffer);
    int err;
    const char *el = "Hello";

    err = bp_array_push(&array, &el);

    EXPECT_EQ(err, 0);
    EXPECT_STRCASEEQ(buffer[0], el);
    EXPECT_EQ(array._size, 1);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, sizeof(char *));
}

TEST(PushElement, EmptyStringElement)
{
    char *buffer[10] = {nullptr};
    bp_array_t array = BP_ARRAY_INIT(buffer);
    int err;
    const char *el = "";

    err = bp_array_push(&array, &el);

    EXPECT_EQ(err, 0);
    EXPECT_STRCASEEQ(buffer[0], el);
    EXPECT_EQ(array._size, 1);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, sizeof(char *));
}

TEST(PushElement, NullStringElement)
{
    char *buffer[10] = {nullptr};
    bp_array_t array = BP_ARRAY_INIT(buffer);
    int err;
    const char *el = nullptr;

    err = bp_array_push(&array, &el);

    EXPECT_EQ(err, 0);
    EXPECT_STRCASEEQ(buffer[0], el);
    EXPECT_EQ(array._size, 1);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, sizeof(char *));
}

TEST(PushElement, ArrayElement)
{
    uint16_t buffer[10][32] = {0};
    bp_array_t array        = BP_ARRAY_INIT(buffer);
    int err;
    uint16_t el[32] = {10};

    err = bp_array_push(&array, &el);

    EXPECT_EQ(err, 0);
    for (int i = 0; i < 32; ++i) {
        EXPECT_EQ(buffer[0][i], el[i]);
    }
    EXPECT_EQ(array._size, 1);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 64);
}

TEST(PushElement, StructElement)
{
    struct {
        uint16_t x;
        uint16_t y;
    } buffer[10]     = {0};
    bp_array_t array = BP_ARRAY_INIT(buffer);
    int err;
    struct {
        uint16_t x;
        uint16_t y;
    } el = {.x = 10, .y = 20};

    err = bp_array_push(&array, &el);

    EXPECT_EQ(err, 0);
    EXPECT_EQ(buffer[0].x, el.x);
    EXPECT_EQ(buffer[0].y, el.y);
    EXPECT_EQ(array._size, 1);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 4);
}

TEST(PushElement, OnNullArray)
{
    int err;
    uint16_t el = 10;

    err = bp_array_push(nullptr, &el);

    EXPECT_EQ(err, -ENODEV);
}

TEST(PushElement, OnNotInitArray)
{
    bp_array_t array = {0};
    int err;
    uint16_t el = 10;

    err = bp_array_push(&array, &el);

    EXPECT_EQ(err, -ENOMEM);
    EXPECT_EQ(array._array, nullptr);
    EXPECT_EQ(array._size, 0);
    EXPECT_EQ(array._capacity, 0);
    EXPECT_EQ(array._element_size, 0);
}

TEST(PushElement, OnEmptyArray)
{
    uint16_t buffer[10] = {0};
    bp_array_t array    = BP_ARRAY_INIT(buffer);
    int err;
    uint16_t el = 10;

    err = bp_array_push(&array, &el);

    EXPECT_EQ(err, 0);
    EXPECT_EQ(buffer[0], el);
    EXPECT_EQ(array._size, 1);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(PushElement, OnArrayWithOneElement)
{
    uint16_t buffer[10] = {0};
    buffer[0]           = 1;
    bp_array_t array    = BP_ARRAY_START(buffer, 1);
    int err;
    uint16_t el = 10;

    err = bp_array_push(&array, &el);

    EXPECT_EQ(err, 0);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], el);
    EXPECT_EQ(array._size, 2);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(PushElement, OnFullArray)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 10; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 10);
    int err;
    uint16_t el = 10;

    err = bp_array_push(&array, &el);

    EXPECT_EQ(err, -ENOMEM);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(buffer[i], i + 1);
    }
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}

TEST(PushElement, OnFullLastOneArray)
{
    uint16_t buffer[10] = {0};
    for (int i = 0; i < 9; ++i) {
        buffer[i] = i + 1;
    }
    bp_array_t array = BP_ARRAY_START(buffer, 9);
    int err;
    uint16_t el = 10;

    err = bp_array_push(&array, &el);

    EXPECT_EQ(err, 0);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(buffer[i], i + 1);
    }
    EXPECT_EQ(array._size, 10);
    EXPECT_EQ(array._capacity, 10);
    EXPECT_EQ(array._element_size, 2);
}
