/**
 * @file test_stack.cpp
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 28/09/2021
 *
 * @copyright Matheus T. dos Santos todos os direitos reservados (c) 2021
 *
 */
#include "doctest.h"

#include "bp_stack.h"

TEST_SUITE("Stack | Normal flow")
{
    TEST_CASE("Push an element to array")
    {
        int stack[10]   = {0};
        bp_array_t coll = BP_ARRAY_INIT(stack);
        int el          = 10;
        int err;

        err = bp_stack_push(&coll, &el);

        REQUIRE(err == 0);
        REQUIRE(stack[0] == 10);
        REQUIRE(coll._size == 1);
    }

    TEST_CASE("Pop an element from stack")
    {
        int stack[10] = {
            1, 2, 3, 0, 0, 0, 0, 0, 0, 0,
        };
        bp_array_t coll = BP_ARRAY_START(stack, 3);
        int el;
        int err;

        err = bp_stack_pop(&coll, &el);

        REQUIRE(err == 0);
        REQUIRE(coll._size == 2);
        REQUIRE(el == 3);
    }

    TEST_CASE("Peek an element of the stack")
    {
        int stack[10] = {
            1, 2, 3, 0, 0, 0, 0, 0, 0, 0,
        };
        bp_array_t coll = BP_ARRAY_START(stack, 3);
        int *el;

        el = (int *) bp_stack_peek(&coll);

        REQUIRE(el != nullptr);
        REQUIRE(*el == 3);
        REQUIRE(stack[2] == 3);
        REQUIRE(coll._size == 3);
    }
}

TEST_SUITE("Stack | Invalid Parameter")
{
    TEST_CASE("Null stack argument in push function")
    {
        int el = 4;
        int err;

        err = bp_stack_push(nullptr, &el);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null element argument in push function")
    {
        int err;
        int stack[10]   = {0};
        bp_array_t coll = BP_ARRAY_INIT(stack);

        err = bp_stack_push(&coll, nullptr);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null stack argument in pop function")
    {
        int el = 4;
        int err;

        err = bp_stack_pop(nullptr, &el);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null element argument in pop function")
    {
        int err;
        int stack[10]   = {0};
        bp_array_t coll = BP_ARRAY_INIT(stack);

        err = bp_stack_pop(&coll, nullptr);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null stack argument in peek function")
    {
        int *el;

        el = (int *) bp_stack_peek(nullptr);

        REQUIRE(el == nullptr);
    }
}

TEST_SUITE("Stack | Error flow")
{
    TEST_CASE("Push an element on full stack")
    {
        int stack[10]   = {0};
        bp_array_t coll = BP_ARRAY_START(stack, 10);
        int el          = 10;
        int err;

        err = bp_stack_push(&coll, &el);

        REQUIRE(err != 0);
    }

    TEST_CASE("Pop an element from an empty stack")
    {
        int stack[10]   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        bp_array_t coll = BP_ARRAY_INIT(stack);
        int el          = 0;
        int err;

        err = bp_stack_pop(&coll, &el);

        REQUIRE(err != 0);
        REQUIRE(el == 0);
        REQUIRE(coll._size == 0);
    }

    TEST_CASE("Peek an element from an empty stack")
    {
        int stack[10]   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        bp_array_t coll = BP_ARRAY_INIT(stack);
        int *el;

        el = (int *) bp_stack_peek(&coll);

        REQUIRE(el == nullptr);
        REQUIRE(coll._size == 0);
    }
}

TEST_SUITE("Stack | Iterator test")
{
    TEST_CASE("Manual for")
    {
        int stack[10]   = {1, 2, 3, 4, 5, 6, 7, 0, 0, 0};
        bp_array_t coll = BP_ARRAY_START(stack, 7);
        bp_iter_t it    = bp_stack_iter(&coll);
        usize i         = 6;

        for (int *el = (int *) it.init(&it); it.next(&it); el = (int *) it.get(&it)) {
            REQUIRE(*el == stack[i]);
            i -= 1;
        }

        REQUIRE(it.current.idx == 0);
    }

    TEST_CASE("Foreach macro usage")
    {
        int stack[10]   = {1, 2, 3, 4, 5, 6, 7, 0, 0, 0};
        bp_array_t coll = BP_ARRAY_START(stack, 7);
        bp_iter_t it    = bp_stack_iter(&coll);
        usize i         = 6;

        BP_FOREACH(int, el, &it)
        {
            REQUIRE(*el == stack[i]);
            i -= 1;
        }

        REQUIRE(it.current.idx == 0);
    }
}
