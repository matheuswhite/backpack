/**
 * @file ring_iter.cpp
 * @author Matheus T. dos Santos (tenoriomatheus0@edge.ufal.br)
 * @brief
 * @version 0.1
 * @date 08/03/2023
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <gtest/gtest.h>
#include "bp_iter2.h"
#include "bp_ring.h"

TEST(RingOnceIter, Empty)
{
    uint16_t buffer[10] = {0};
    bp_ring_t ring      = BP_RING_INIT(buffer);
    bp_iterator_t it;

    it = bp_ring_once_iterator(&ring);

    EXPECT_EQ(ring._size, 0);
    BP_FOREACH_FOWARD(uint16_t, el, &it)
    {
        EXPECT_TRUE(false);
    }
    EXPECT_EQ(bp_iterator_get(&it), nullptr);
}

TEST(RingOnceIter, OneItem)
{
    uint16_t buffer[10] = {0};
    bp_ring_t ring      = BP_RING_INIT(buffer);
    bp_iterator_t it;
    int err;
    int counter = 1;

    for (int i = 1; i <= 1; ++i) {
        err = bp_ring_push(&ring, &i);
        EXPECT_EQ(err, 0);
    }

    it = bp_ring_once_iterator(&ring);

    EXPECT_EQ(ring._size, 1);
    BP_FOREACH_FOWARD(uint16_t, el, &it)
    {
        EXPECT_EQ(counter, *el);
        EXPECT_LE(counter, 1);
        counter += 1;
    }
    EXPECT_EQ(bp_iterator_get(&it), &buffer[0]);
}

TEST(RingOnceIter, TwoItems)
{
    uint16_t buffer[10] = {0};
    bp_ring_t ring      = BP_RING_INIT(buffer);
    bp_iterator_t it;
    int err;
    int counter = 1;

    for (int i = 1; i <= 2; ++i) {
        err = bp_ring_push(&ring, &i);
        EXPECT_EQ(err, 0);
    }

    it = bp_ring_once_iterator(&ring);

    EXPECT_EQ(ring._size, 2);
    BP_FOREACH_FOWARD(uint16_t, el, &it)
    {
        EXPECT_EQ(counter, *el);
        EXPECT_LE(counter, 2);
        counter += 1;
    }
    EXPECT_EQ(bp_iterator_get(&it), &buffer[1]);
}

TEST(RingOnceIter, Full)
{
    uint16_t buffer[10] = {0};
    bp_ring_t ring      = BP_RING_INIT(buffer);
    bp_iterator_t it;
    uint16_t *last;
    int err;
    int counter = 1;

    for (int i = 1; i <= 10; ++i) {
        err = bp_ring_push(&ring, &i);
        EXPECT_EQ(err, 0);
    }

    it = bp_ring_once_iterator(&ring);

    EXPECT_EQ(ring._size, 10);
    BP_FOREACH_FOWARD(uint16_t, el, &it)
    {
        EXPECT_EQ(counter, *el);
        EXPECT_LE(counter, 10);
        counter += 1;
    }
    EXPECT_EQ(bp_iterator_get(&it), &buffer[9]);
}
