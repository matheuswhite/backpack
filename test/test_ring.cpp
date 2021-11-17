/**
 * @file test_ring.cpp
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 30/09/2021
 *
 * @copyright Matheus T. dos Santos todos os direitos reservados (c) 2021
 *
 */
#include "doctest.h"

#include "bp_ring.h"

extern "C" {
#include <stdio.h>

typedef struct {
    usize id;
    u16_t value;
} id_value16_t;

static bool id_value_cmp_id(void *el, void *param)
{
    id_value16_t *el_ = (id_value16_t *) el;
    usize *id         = (usize *) param;

    return el_->id == *id;
}
}

TEST_SUITE("Ring | Normal flow")
{
    TEST_CASE("Push an element to ring")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        int el         = 7;
        int err;

        err = bp_ring_push(&coll, &el);

        REQUIRE(err == 0);
        REQUIRE(ring[0] == 7);
        REQUIRE(coll._size == 1);
    }

    TEST_CASE("Push an element to full ring")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        int el         = 7;
        int err;

        for (int i = 0; i < coll._max_size; ++i) {
            bp_ring_push(&coll, &i);
        }
        err = bp_ring_push(&coll, &el);

        REQUIRE(err == 0);
        REQUIRE(ring[0] == 7);
        REQUIRE(coll._size == 10);
    }

    TEST_CASE("Get an element from ring")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        int *el;

        for (int i = 0; i < 5; ++i) {
            bp_ring_push(&coll, &i);
        }
        el = (int *) bp_ring_get(&coll, 2);

        REQUIRE(el != nullptr);
        REQUIRE(*el == 2);
        REQUIRE(coll._size == 5);
    }

    TEST_CASE("Peek an element from ring")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        int *el;
        int pop_el;

        for (int i = 0; i < 5; ++i) {
            bp_ring_push(&coll, &i);
        }
        bp_ring_pop(&coll, &pop_el);
        el = (int *) bp_ring_peek(&coll);

        REQUIRE(el != nullptr);
        REQUIRE(*el == 1);
        REQUIRE(coll._size == 4);
    }

    TEST_CASE("Pop an element from ring")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        int el         = 11;
        int err;

        for (int i = 1; i <= 5; ++i) {
            bp_ring_push(&coll, &i);
        }
        err = bp_ring_pop(&coll, &el);

        REQUIRE(err == 0);
        REQUIRE(el == 1);
        REQUIRE(coll._size == 4);
    }

    TEST_CASE("Delete the top element from ring")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        int err;

        for (int i = 1; i <= 5; ++i) {
            bp_ring_push(&coll, &i);
        }
        err = bp_ring_pop(&coll, NULL);

        REQUIRE(err == 0);
        REQUIRE(coll._size == 4);
    }

    TEST_CASE("Find an element in the ring")
    {
        int ring[10]    = {0};
        bp_ring_t coll  = BP_RING_INIT(ring);
        int expected_el = 4;
        int *el;

        for (int i = 1; i <= 10; ++i) {
            bp_ring_push(&coll, &i);
        }

        el = (int *) bp_ring_find(&coll, &expected_el, nullptr);

        REQUIRE(el != nullptr);
        REQUIRE(*el == expected_el);
    }

    TEST_CASE("Find an element in the ring by its id")
    {
        id_value16_t ring[10] = {0};
        bp_ring_t coll        = BP_RING_INIT(ring);
        usize el_id           = 4;
        id_value16_t *el;
        id_value16_t ref_el;
        for (usize i = 0; i < 10; ++i) {
            ref_el.id    = i + 1;
            ref_el.value = i * i;
            bp_ring_push(&coll, &ref_el);
        }

        el = (id_value16_t *) bp_ring_find(&coll, &el_id, id_value_cmp_id);

        REQUIRE(el != nullptr);
        REQUIRE(el->id == 4);
        REQUIRE(el->value == 9);
    }

    TEST_CASE("Get the index of a ring element")
    {
        int ring[10]    = {0};
        bp_ring_t coll  = BP_RING_INIT(ring);
        int expected_el = 4;
        int el;
        usize idx;

        for (int i = 1; i <= 10; ++i) {
            bp_ring_push(&coll, &i);
        }
        bp_ring_pop(&coll, &el);

        idx = bp_ring_find_idx(&coll, &expected_el, nullptr);

        REQUIRE(idx == 2);
    }

    TEST_CASE("Get the index of a ring element by its id")
    {
        id_value16_t ring[10] = {0};
        bp_ring_t coll        = BP_RING_INIT(ring);
        usize el_id           = 4;
        id_value16_t ref_el;
        usize idx;
        for (usize i = 0; i < 10; ++i) {
            ref_el.id    = i + 1;
            ref_el.value = i * i;
            bp_ring_push(&coll, &ref_el);
        }
        bp_ring_pop(&coll, &ref_el);

        idx = bp_ring_find_idx(&coll, &el_id, id_value_cmp_id);

        REQUIRE(idx == 2);
    }

    TEST_CASE("Drop all elements from ring")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        int err;

        for (int i = 1; i <= 10; ++i) {
            bp_ring_push(&coll, &i);
        }
        REQUIRE(coll._size == 10);

        err = bp_ring_clear(&coll);

        REQUIRE(err == 0);
        REQUIRE(coll._size == 0);
    }

    TEST_CASE("Get the size of the ring")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        usize size;

        for (int i = 1; i <= 10; ++i) {
            bp_ring_push(&coll, &i);
        }
        size = bp_ring_size(&coll);

        REQUIRE(coll._size == 10);
        REQUIRE(size == 10);
    }

    TEST_CASE("Get the size of full ring after push")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        usize size;
        int el = 15;

        for (int i = 1; i <= 10; ++i) {
            bp_ring_push(&coll, &i);
        }
        size = bp_ring_size(&coll);

        REQUIRE(coll._size == 10);
        REQUIRE(size == 10);

        bp_ring_push(&coll, &el);
        size = bp_ring_size(&coll);

        REQUIRE(coll._size == 10);
        REQUIRE(size == 10);
    }
}

TEST_SUITE("Ring | Invalid Parameters")
{
    TEST_CASE("Null ring argument in get function")
    {
        void *el = nullptr;

        el = bp_ring_get(nullptr, 0);

        REQUIRE(el == nullptr);
    }

    TEST_CASE("Null ring argument in peek function")
    {
        void *el = nullptr;

        el = bp_ring_peek(nullptr);

        REQUIRE(el == nullptr);
    }

    TEST_CASE("Null ring argument in pop function")
    {
        int el = 7;
        int err;

        err = bp_ring_pop(nullptr, &el);

        REQUIRE(err != 0);
        REQUIRE(el == 7);
    }

    TEST_CASE("Null ring argument in push function")
    {
        int el = 7;
        int err;

        err = bp_ring_push(nullptr, &el);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null element argument in push function")
    {
        int err;
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);

        err = bp_ring_push(&coll, nullptr);

        REQUIRE(err != 0);
        REQUIRE(coll._size == 0);
    }

    TEST_CASE("Null ring argument in find index function")
    {
        int el = 7;
        usize idx;

        idx = bp_ring_find_idx(nullptr, &el, nullptr);

        REQUIRE(idx == BP_RING_INVALID_INDEX);
    }

    TEST_CASE("Null param argument in find index function")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        usize idx;

        idx = bp_ring_find_idx(&coll, nullptr, nullptr);

        REQUIRE(idx == BP_RING_INVALID_INDEX);
    }

    TEST_CASE("Null ring argument in find function")
    {
        int el = 7;
        int *found_el;

        found_el = (int *) bp_ring_find(nullptr, &el, nullptr);

        REQUIRE(found_el == nullptr);
    }

    TEST_CASE("Null ring param in find function")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        int *el;

        el = (int *) bp_ring_find(&coll, nullptr, nullptr);

        REQUIRE(el == nullptr);
    }

    TEST_CASE("Null ring argument in clear function")
    {
        int err;

        err = bp_ring_clear(nullptr);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null ring argument in size function")
    {
        usize size;

        size = bp_ring_size(nullptr);

        REQUIRE(size == 0);
    }
}

TEST_SUITE("Ring | Error flow")
{
    TEST_CASE("Get an element from empty ring")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        int *el        = nullptr;

        el = (int *) bp_ring_get(&coll, 0);

        REQUIRE(el == nullptr);
    }

    TEST_CASE("Peek an element from empty ring")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        int *el        = nullptr;

        el = (int *) bp_ring_peek(&coll);

        REQUIRE(el == nullptr);
    }

    TEST_CASE("Pop an element from empty ring")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        int el;
        int err;

        err = bp_ring_pop(&coll, &el);

        REQUIRE(err != 0);
    }

    TEST_CASE("Search a non existent element in ring")
    {
        int ring[10]    = {0};
        bp_ring_t coll  = BP_RING_INIT(ring);
        int expected_el = 11;
        int *el;

        for (int i = 1; i <= 10; ++i) {
            bp_ring_push(&coll, &i);
        }

        el = (int *) bp_ring_find(&coll, &expected_el, nullptr);

        REQUIRE(el == nullptr);
    }

    TEST_CASE("Search a non existent element in ring by its id")
    {
        id_value16_t ring[10] = {0};
        bp_ring_t coll        = BP_RING_INIT(ring);
        usize el_id           = 11;
        id_value16_t *el;
        id_value16_t ref_el;
        for (usize i = 0; i < 10; ++i) {
            ref_el.id    = i + 1;
            ref_el.value = i * i;
            bp_ring_push(&coll, &ref_el);
        }

        el = (id_value16_t *) bp_ring_find(&coll, &el_id, id_value_cmp_id);

        REQUIRE(el == nullptr);
    }

    TEST_CASE("Get the index of an element not in ring")
    {
        int ring[10]    = {0};
        bp_ring_t coll  = BP_RING_INIT(ring);
        int expected_el = 11;
        int el;
        usize idx;

        for (int i = 1; i <= 10; ++i) {
            bp_ring_push(&coll, &i);
        }
        bp_ring_pop(&coll, &el);

        idx = bp_ring_find_idx(&coll, &expected_el, nullptr);

        REQUIRE(idx == BP_RING_INVALID_INDEX);
    }

    TEST_CASE("Get the index of an element not in ring by its id")
    {
        id_value16_t ring[10] = {0};
        bp_ring_t coll        = BP_RING_INIT(ring);
        usize el_id           = 11;
        id_value16_t ref_el;
        usize idx;
        for (usize i = 0; i < 10; ++i) {
            ref_el.id    = i + 1;
            ref_el.value = i * i;
            bp_ring_push(&coll, &ref_el);
        }
        bp_ring_pop(&coll, &ref_el);

        idx = bp_ring_find_idx(&coll, &el_id, id_value_cmp_id);

        REQUIRE(idx == BP_RING_INVALID_INDEX);
    }
}

TEST_SUITE("Ring | Iterator test")
{
    TEST_CASE("Manual for")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        bp_iter_t it   = bp_ring_iter(&coll);
        int i;

        for (i = 0; i < 12; ++i) {
            bp_ring_push(&coll, &i);
        }

        i = 2;
        for (int *el = (int *) it.init(&it); it.next(&it); el = (int *) it.get(&it)) {
            REQUIRE(*el == ring[i]);
            i += 1;
        }

        REQUIRE(it.current.idx == 2);
    }

    TEST_CASE("Foreach macro usage")
    {
        int ring[10]   = {0};
        bp_ring_t coll = BP_RING_INIT(ring);
        bp_iter_t it   = bp_ring_iter(&coll);
        int i;

        for (i = 0; i < 12; ++i) {
            bp_ring_push(&coll, &i);
        }

        i = 2;
        BP_FOREACH(int, el, &it)
        {
            REQUIRE(*el == ring[i]);
            i += 1;
        }

        REQUIRE(it.current.idx == 2);
    }
}
