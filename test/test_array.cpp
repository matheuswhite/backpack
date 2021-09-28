/**
 * @file test_array.cpp
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 19/09/2021
 *
 * @copyright Matheus T. dos Santos todos os direitos reservados (c) 2021
 *
 */
#include "doctest.h"

#include "bp_array.h"

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

TEST_SUITE("Normal flow")
{
    TEST_CASE("Push an element to array")
    {
        int array[10]   = {0};
        bp_array_t coll = BP_ARRAY_INIT(array);
        int el          = 10;
        int err;

        err = bp_array_push(&coll, &el);

        REQUIRE(err == 0);
        REQUIRE(array[0] == 10);
        REQUIRE(coll._size == 1);
    }


    TEST_CASE("Get a element from array")
    {
        int array[10]   = {0};
        bp_array_t coll = BP_ARRAY_INIT(array);
        int expected_el = 10;
        int *el;

        bp_array_push(&coll, &expected_el);
        el = (int *) bp_array_get(&coll, 0);

        REQUIRE(*el == expected_el);
    }


    TEST_CASE("Delete the first array element")
    {
        int array[10]   = {1, 2, 3, 4, 0, 0, 0, 0, 0, 0};
        bp_array_t coll = BP_ARRAY_START(array, 4);
        int err;

        err = bp_array_del(&coll, 0);

        REQUIRE(err == 0);
        REQUIRE(array[0] == 2);
        REQUIRE(array[1] == 3);
        REQUIRE(array[2] == 4);
        REQUIRE(coll._size == 3);
    }

    TEST_CASE("Delete a middle array element")
    {
        int array[10]   = {1, 2, 3, 4, 0, 0, 0, 0, 0, 0};
        bp_array_t coll = BP_ARRAY_START(array, 4);
        int err;

        err = bp_array_del(&coll, 1);

        REQUIRE(err == 0);
        REQUIRE(array[0] == 1);
        REQUIRE(array[1] == 3);
        REQUIRE(array[2] == 4);
        REQUIRE(coll._size == 3);
    }

    TEST_CASE("Delete the last array element")
    {
        int array[10]   = {1, 2, 3, 4, 0, 0, 0, 0, 0, 0};
        bp_array_t coll = BP_ARRAY_START(array, 4);
        int err;

        err = bp_array_del(&coll, 3);

        REQUIRE(err == 0);
        REQUIRE(array[0] == 1);
        REQUIRE(array[1] == 2);
        REQUIRE(array[2] == 3);
        REQUIRE(coll._size == 3);
    }


    TEST_CASE("Find an element in the array")
    {
        int array[10]   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        bp_array_t coll = BP_ARRAY_START(array, 10);
        int expected_el = 4;
        int *el;

        el = (int *) bp_array_find(&coll, &expected_el, nullptr);

        REQUIRE(*el == expected_el);
    }

    TEST_CASE("Find an element in the array by its id")
    {
        id_value16_t array[10] = {0};
        for (usize i = 0; i < 10; ++i) {
            array[i].id    = i + 1;
            array[i].value = i * i;
        }
        bp_array_t coll = BP_ARRAY_START(array, 10);
        usize el_id     = 4;
        id_value16_t *el;

        el = (id_value16_t *) bp_array_find(&coll, &el_id, id_value_cmp_id);

        REQUIRE(el != nullptr);
        REQUIRE(el->id == 4);
        REQUIRE(el->value == 9);
    }

    TEST_CASE("Get the index of an array element")
    {
        int array[10]   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        bp_array_t coll = BP_ARRAY_START(array, 10);
        int expected_el = 4;
        usize idx;

        idx = bp_array_find_idx(&coll, &expected_el, nullptr);

        REQUIRE(idx == 3);
    }

    TEST_CASE("Get the index of an array element by its id")
    {
        id_value16_t array[10] = {0};
        for (usize i = 0; i < 10; ++i) {
            array[i].id    = i + 1;
            array[i].value = i * i;
        }
        bp_array_t coll = BP_ARRAY_START(array, 10);
        int el_id       = 4;
        usize idx;

        idx = bp_array_find_idx(&coll, &el_id, id_value_cmp_id);

        for (auto &a : array) {
            printf("element %lu: %d\n", a.id, a.value);
        }
        REQUIRE(idx == 3);
        REQUIRE(array[idx].id == el_id);
        REQUIRE(array[idx].value == 9);
    }

    TEST_CASE("Drop all elements in the array")
    {
        int array[10]   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        bp_array_t coll = BP_ARRAY_START(array, 10);
        int err;

        err = bp_array_clear(&coll);

        REQUIRE(err == 0);
        REQUIRE(coll._size == 0);
    }

    TEST_CASE("Get the size of the array")
    {
        int array[10]   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        bp_array_t coll = BP_ARRAY_START(array, 10);
        usize size;

        size = bp_array_size(&coll);

        REQUIRE(size == coll._size);
    }
}

TEST_SUITE("Invalid Parameters")
{
    TEST_CASE("Null array argument in get function")
    {
        void *el = nullptr;

        el = bp_array_get(nullptr, 0);

        REQUIRE(el == nullptr);
    }

    TEST_CASE("Null array argument in push function")
    {
        int err;
        int el = 7;

        err = bp_array_push(nullptr, &el);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null element argument in push function")
    {
        int err;
        int array[10]   = {0};
        bp_array_t coll = BP_ARRAY_INIT(array);

        err = bp_array_push(&coll, nullptr);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null array argument in delete function")
    {
        int err;

        err = bp_array_del(nullptr, 0);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null array argument in find index function")
    {
        usize idx;
        int param = 7;

        idx = bp_array_find_idx(nullptr, &param, nullptr);

        REQUIRE(idx == BP_ARRAY_INVALID_INDEX);
    }

    TEST_CASE("Null param argument in find index function")
    {
        usize idx;
        int array[10]   = {0};
        bp_array_t coll = BP_ARRAY_INIT(array);

        idx = bp_array_find_idx(&coll, nullptr, nullptr);

        REQUIRE(idx == BP_ARRAY_INVALID_INDEX);
    }

    TEST_CASE("Null array argument in find function")
    {
        int *el;
        int param = 7;

        el = (int *) bp_array_find(nullptr, &param, nullptr);

        REQUIRE(el == nullptr);
    }

    TEST_CASE("Null param argument in find function")
    {
        void *el;
        int array[10]   = {0};
        bp_array_t coll = BP_ARRAY_INIT(array);

        el = (int *) bp_array_find(&coll, nullptr, nullptr);

        REQUIRE(el == nullptr);
    }

    TEST_CASE("Null array argument in clear function")
    {
        int err;

        err = bp_array_clear(nullptr);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null array argument in size function")
    {
        usize size;

        size = bp_array_size(nullptr);

        REQUIRE(size == 0);
    }
}

TEST_SUITE("Error flow")
{
    TEST_CASE("Push an element on full array")
    {
        int array[10]   = {0};
        bp_array_t coll = BP_ARRAY_START(array, 10);
        int el          = 10;
        int err;

        err = bp_array_push(&coll, &el);

        REQUIRE(err != 0);
    }

    TEST_CASE("Get a element from an empty array")
    {
        int array[10]   = {0};
        bp_array_t coll = BP_ARRAY_INIT(array);
        int *el         = nullptr;

        el = (int *) bp_array_get(&coll, 0);

        REQUIRE(el == nullptr);
    }

    TEST_CASE("Delete from empty array")
    {
        int array[10]   = {0};
        bp_array_t coll = BP_ARRAY_INIT(array);
        int err;

        err = bp_array_del(&coll, 0);

        REQUIRE(err != 0);
    }

    TEST_CASE("Search a non existent element")
    {
        int array[10]   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        bp_array_t coll = BP_ARRAY_START(array, 10);
        int expected_el = 11;
        int *el         = nullptr;

        el = (int *) bp_array_find(&coll, &expected_el, nullptr);

        REQUIRE(el == nullptr);
    }

    TEST_CASE("Get the index of an element not in array")
    {
        int array[10]   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        bp_array_t coll = BP_ARRAY_START(array, 10);
        int expected_el = 11;
        usize idx;

        idx = bp_array_find_idx(&coll, &expected_el, nullptr);

        REQUIRE(idx == BP_ARRAY_INVALID_INDEX);
    }
}

TEST_SUITE("Iterator test")
{
    TEST_CASE("Manual for")
    {
        int array[10]   = {1, 2, 3, 4, 5, 6, 7, 0, 0, 0};
        bp_array_t coll = BP_ARRAY_START(array, 7);
        bp_iter_t it    = bp_array_iter(&coll);
        int i           = 0;

        for (int *el = (int *) it.init(&it); it.next(&it); el = (int *) it.get(&it)) {
            REQUIRE(*el == array[i]);
            i += 1;
        }

        REQUIRE(it.current.idx == 7);
    }

    TEST_CASE("Foreach macro usage")
    {
        int array[10]   = {1, 2, 3, 4, 5, 6, 7, 0, 0, 0};
        bp_array_t coll = BP_ARRAY_START(array, 7);
        bp_iter_t it    = bp_array_iter(&coll);
        int i           = 0;

        BP_FOREACH(int, el, &it)
        {
            REQUIRE(*el == array[i]);
            i += 1;
        }

        REQUIRE(it.current.idx == 7);
    }
}
