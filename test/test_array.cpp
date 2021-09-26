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


    TEST_CASE("Get the index of an array element")
    {
        int array[10]   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        bp_array_t coll = BP_ARRAY_START(array, 10);
        int expected_el = 4;
        usize idx;

        idx = bp_array_find_idx(&coll, &expected_el, nullptr);

        REQUIRE(idx == 3);
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
