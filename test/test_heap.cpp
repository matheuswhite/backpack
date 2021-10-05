/**
 * @file test_heap.cpp
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 01/10/2021
 *
 * @copyright Matheus T. dos Santos todos os direitos reservados (c) 2021
 *
 */
#include "doctest.h"

#include <doctest.h>
#include <random>
#include "bp_heap.h"

extern "C" {
typedef struct {
    usize key;
    u16_t value;
} bp_kv_t;

static int bp_int_cmp(void *left, void *right)
{
    u32_t *left_int  = (u32_t *) left;
    u32_t *right_int = (u32_t *) right;

    return ((int) *left_int) - ((int) *right_int);
}

static int bp_kv_cmp(void *left, void *right)
{
    bp_kv_t *left_kv  = (bp_kv_t *) left;
    bp_kv_t *right_kv = (bp_kv_t *) right;

    return ((int) left_kv->key) - ((int) right_kv->key);
}

static bool bp_kv_key_cmp(void *el, void *param)
{
    bp_kv_t *el_ = (bp_kv_t *) el;
    usize *key   = (usize *) param;

    return *key == el_->key;
}
}

extern const char *getCurrentTestName();

TEST_SUITE("Min Heap | Normal flow")
{
    TEST_CASE("Push some elements on the heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el;
        u32_t parent;
        int err;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el  = rand() % 0x7fFFffFF;
            err = bp_heap_push(&heap, &el);
            REQUIRE(err == 0);

            for (int j = 1; j < heap._coll._size; ++j) {
                parent = buffer[(j - 1) >> 1];
                REQUIRE(parent <= buffer[j]);
            }
        }
    }

    TEST_CASE("Check heap top after some pushes")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el;
        u32_t minor;
        u32_t *top_el;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            if (el < minor) {
                minor = el;
            }
            bp_heap_push(&heap, &el);
            top_el = (u32_t *) bp_heap_top(&heap);

            REQUIRE(top_el != nullptr);
            REQUIRE(*top_el == minor);
        }
    }

    TEST_CASE("Pop some heap elements")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el;
        u32_t top_el;
        int err;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        for (int i = 0; i < 20; ++i) {
            top_el = *(u32_t *) bp_heap_top(&heap);
            err    = bp_heap_pop(&heap, &el);

            REQUIRE(err == 0);
            REQUIRE(top_el == el);
            REQUIRE(heap._coll._size == (20 - i - 1));
        }
    }

    TEST_CASE("Delete a heap element")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el;
        u32_t target_el;
        u32_t parent;
        int err;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }
        target_el = buffer[rand() % 20];

        err = bp_heap_del(&heap, &target_el, nullptr);

        REQUIRE(err == 0);
        REQUIRE(heap._coll._size == 19);
        REQUIRE(buffer[0] != target_el);
        for (int j = 1; j < heap._coll._size; ++j) {
            parent = buffer[(j - 1) >> 1];
            REQUIRE(buffer[j] != target_el);
            REQUIRE(parent <= buffer[j]);
        }
    }

    TEST_CASE("Delete a heap element by its id")
    {
        bp_kv_t buffer[20] = {0};
        bp_heap_t heap     = BP_MIN_HEAP_INIT(buffer, bp_kv_cmp);
        bp_kv_t el;
        bp_kv_t target_el;
        bp_kv_t parent;
        int err;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el.key   = rand() % 0x7fFFffFF;
            el.value = rand() % 0xffFF;
            bp_heap_push(&heap, &el);
        }
        target_el = buffer[rand() % 20];

        err = bp_heap_del(&heap, &target_el.key, bp_kv_key_cmp);

        REQUIRE(err == 0);
        REQUIRE(heap._coll._size == 19);
        REQUIRE(buffer[0].key != target_el.key);
        REQUIRE(buffer[0].value != target_el.value);
        for (int j = 1; j < heap._coll._size; ++j) {
            parent = buffer[(j - 1) >> 1];
            REQUIRE(buffer[j].key != target_el.key);
            REQUIRE(buffer[j].value != target_el.value);
            REQUIRE(parent.key <= buffer[j].key);
        }
    }

    TEST_CASE("Drop all elements from heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el;
        int err;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        err = bp_heap_clear(&heap);

        REQUIRE(err == 0);
        REQUIRE(heap._coll._size == 0);
    }

    TEST_CASE("Find an element in the heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el;
        u32_t target_el;
        u32_t *found_el;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }
        target_el = buffer[rand() % 20];

        found_el = (u32_t *) bp_heap_find(&heap, &target_el, nullptr);

        REQUIRE(found_el != nullptr);
        REQUIRE(*found_el == target_el);
        REQUIRE(heap._coll._size == 20);
    }

    TEST_CASE("Find an element in the heap by its id")
    {
        bp_kv_t buffer[20] = {0};
        bp_heap_t heap     = BP_MIN_HEAP_INIT(buffer, bp_kv_cmp);
        bp_kv_t el;
        bp_kv_t target_el;
        bp_kv_t *found_el;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el.key   = rand() % 0x7fFFffFF;
            el.value = rand() % 0xffFF;
            bp_heap_push(&heap, &el);
        }
        target_el = buffer[rand() % 20];

        found_el = (bp_kv_t *) bp_heap_find(&heap, &target_el.key, bp_kv_key_cmp);

        REQUIRE(found_el != nullptr);
        REQUIRE(found_el->key == target_el.key);
        REQUIRE(found_el->value == target_el.value);
        REQUIRE(heap._coll._size == 20);
    }
}

TEST_SUITE("Min Heap | Error flow")
{
    TEST_CASE("Push an element on full heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el;
        int err;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el  = rand() % 0x7fFFffFF;
            err = bp_heap_push(&heap, &el);
        }
        el  = rand() % 0x7fFFffFF;
        err = bp_heap_push(&heap, &el);

        REQUIRE(err != 0);
    }

    TEST_CASE("Check top on the empty heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        u32_t *top_el;

        top_el = (u32_t *) bp_heap_top(&heap);

        REQUIRE(heap._coll._size == 0);
        REQUIRE(top_el == nullptr);
    }

    TEST_CASE("Pop element on the empty heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el         = 7;
        int err;

        err = bp_heap_pop(&heap, &el);

        REQUIRE(heap._coll._size == 0);
        REQUIRE(err != 0);
        REQUIRE(el == 7);
    }

    TEST_CASE("Delete an element at empty heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el         = 7;
        int err;

        err = bp_heap_del(&heap, &el, nullptr);

        REQUIRE(heap._coll._size == 0);
        REQUIRE(err != 0);
    }

    TEST_CASE("Delete an element at empty heap by its id")
    {
        bp_kv_t buffer[20] = {0};
        bp_heap_t heap     = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        bp_kv_t el         = {
            .key   = 7,
            .value = 10,
        };
        int err;

        err = bp_heap_del(&heap, &el.key, bp_kv_key_cmp);

        REQUIRE(heap._coll._size == 0);
        REQUIRE(err != 0);
    }

    TEST_CASE("Search a non existent element in the heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el;
        u32_t *found_el;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        el = rand() % 0x7fFFffFF;
        for (int i = 0; i < 20; ++i) {
            if (el == buffer[i]) {
                el = rand() % 0x7fFFffFF;
                i  = -1;
            }
        }

        found_el = (u32_t *) bp_heap_find(&heap, &el, nullptr);

        REQUIRE(found_el == nullptr);
    }

    TEST_CASE("Search a non existent element in the heap by its id")
    {
        bp_kv_t buffer[20] = {0};
        bp_heap_t heap     = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        bp_kv_t el;
        bp_kv_t *found_el;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el.key   = rand() % 0x7fFFffFF;
            el.value = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        el.key   = rand() % 0x7fFFffFF;
        el.value = rand() % 0x7fFFffFF;
        for (int i = 0; i < 20; ++i) {
            if (el.key == buffer[i].key) {
                el.key = rand() % 0x7fFFffFF;
                i      = -1;
            }
        }

        found_el = (bp_kv_t *) bp_heap_find(&heap, &el.key, bp_kv_key_cmp);

        REQUIRE(found_el == nullptr);
    }
}

TEST_SUITE("Min Heap | Invalid Parameters")
{
    TEST_CASE("Null heap argument in top function")
    {
        u32_t *el;

        el = (u32_t *) bp_heap_top(nullptr);

        REQUIRE(el == nullptr);
    }

    TEST_CASE("Null heap argument in clear function")
    {
        int err;

        err = bp_heap_clear(nullptr);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null heap argument in pop function")
    {
        int err;
        u32_t el = 7;

        err = bp_heap_pop(nullptr, &el);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null element argument in pop function")
    {
        int err;
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);

        err = bp_heap_pop(&heap, nullptr);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null heap argument in push function")
    {
        int err;
        u32_t el = 7;

        err = bp_heap_push(nullptr, &el);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null element argument in push function")
    {
        int err;
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);

        err = bp_heap_push(&heap, nullptr);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null heap argument in delete function")
    {
        int err;
        u32_t el = 7;

        err = bp_heap_del(nullptr, &el, nullptr);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null param argument in delete function")
    {
        int err;
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);

        err = bp_heap_del(&heap, nullptr, nullptr);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null heap argument in find function")
    {
        u32_t *found_el;
        u32_t el = 7;

        found_el = (u32_t *) bp_heap_find(nullptr, &el, nullptr);

        REQUIRE(found_el == nullptr);
    }

    TEST_CASE("Null param argument in find function")
    {
        u32_t *found_el;
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);

        found_el = (u32_t *) bp_heap_find(&heap, nullptr, nullptr);

        REQUIRE(found_el == nullptr);
    }
}

TEST_SUITE("Min Heap | Iterator")
{
    TEST_CASE("BFS | Manual for")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        bp_iter it       = bp_heap_bfs_iter(&heap);
        u32_t el;
        int i;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        i = 0;
        for (u32_t *element = (u32_t *) it.init(&it); it.next(&it);
             element        = (u32_t *) it.get(&it)) {
            REQUIRE(buffer[i] == *element);
            i++;
        }
    }

    TEST_CASE("DFS | Manual for")
    {
        u32_t buffer[20]    = {0};
        usize lut_index[20] = {0, 1,  3,  7, 15, 16, 8,  17, 18, 4,
                               9, 19, 10, 2, 5,  11, 12, 6,  13, 14};
        bp_heap_t heap      = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        bp_iter it          = bp_heap_dfs_iter(&heap);
        u32_t el;
        int i;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        i = 0;
        for (u32_t *element = (u32_t *) it.init(&it); it.next(&it);
             element        = (u32_t *) it.get(&it)) {
            REQUIRE(buffer[lut_index[i]] == *element);
            i++;
        }
    }

    TEST_CASE("BFS | Foreach macro")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        bp_iter it       = bp_heap_bfs_iter(&heap);
        u32_t el;
        int i;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        i = 0;
        BP_FOREACH(u32_t, element, &it)
        {
            REQUIRE(buffer[i] == *element);
            i++;
        }
    }

    TEST_CASE("DFS | Foreach macro")
    {
        u32_t buffer[20]    = {0};
        usize lut_index[20] = {0, 1,  3,  7, 15, 16, 8,  17, 18, 4,
                               9, 19, 10, 2, 5,  11, 12, 6,  13, 14};
        bp_heap_t heap      = BP_MIN_HEAP_INIT(buffer, bp_int_cmp);
        bp_iter it          = bp_heap_dfs_iter(&heap);
        u32_t el;
        int i;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        i = 0;
        BP_FOREACH(u32_t, element, &it)
        {
            REQUIRE(buffer[lut_index[i]] == *element);
            i++;
        }
    }
}

TEST_SUITE("Max Heap | Normal flow")
{
    TEST_CASE("Push some elements on the heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el;
        u32_t parent;
        int err;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el  = rand() % 0x7fFFffFF;
            err = bp_heap_push(&heap, &el);
            REQUIRE(err == 0);

            for (int j = 1; j < heap._coll._size; ++j) {
                parent = buffer[(j - 1) >> 1];
                REQUIRE(parent >= buffer[j]);
            }
        }
    }

    TEST_CASE("Check heap top after some pushes")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        u32_t major      = 0;
        u32_t el;
        u32_t *top_el;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            if (el > major) {
                major = el;
            }
            bp_heap_push(&heap, &el);
            top_el = (u32_t *) bp_heap_top(&heap);

            REQUIRE(top_el != nullptr);
            REQUIRE(*top_el == major);
        }
    }

    TEST_CASE("Pop some heap elements")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el;
        u32_t top_el;
        int err;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        for (int i = 0; i < 20; ++i) {
            top_el = *(u32_t *) bp_heap_top(&heap);
            err    = bp_heap_pop(&heap, &el);

            REQUIRE(err == 0);
            REQUIRE(top_el == el);
            REQUIRE(heap._coll._size == (20 - i - 1));
        }
    }

    TEST_CASE("Delete a heap element")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el;
        u32_t target_el;
        u32_t parent;
        int err;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }
        target_el = buffer[rand() % 20];

        err = bp_heap_del(&heap, &target_el, nullptr);

        REQUIRE(err == 0);
        REQUIRE(heap._coll._size == 19);
        REQUIRE(buffer[0] != target_el);
        for (int j = 1; j < heap._coll._size; ++j) {
            parent = buffer[(j - 1) >> 1];
            REQUIRE(buffer[j] != target_el);
            REQUIRE(parent >= buffer[j]);
        }
    }

    TEST_CASE("Delete a heap element by its id")
    {
        bp_kv_t buffer[20] = {0};
        bp_heap_t heap     = BP_MAX_HEAP_INIT(buffer, bp_kv_cmp);
        bp_kv_t el;
        bp_kv_t target_el;
        bp_kv_t parent;
        int err;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el.key   = rand() % 0x7fFFffFF;
            el.value = rand() % 0xffFF;
            bp_heap_push(&heap, &el);
        }
        target_el = buffer[rand() % 20];

        err = bp_heap_del(&heap, &target_el.key, bp_kv_key_cmp);

        REQUIRE(err == 0);
        REQUIRE(heap._coll._size == 19);
        REQUIRE(buffer[0].key != target_el.key);
        REQUIRE(buffer[0].value != target_el.value);
        for (int j = 1; j < heap._coll._size; ++j) {
            parent = buffer[(j - 1) >> 1];
            REQUIRE(buffer[j].key != target_el.key);
            REQUIRE(buffer[j].value != target_el.value);
            REQUIRE(parent.key >= buffer[j].key);
        }
    }

    TEST_CASE("Drop all elements from heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el;
        int err;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        err = bp_heap_clear(&heap);

        REQUIRE(err == 0);
        REQUIRE(heap._coll._size == 0);
    }

    TEST_CASE("Find an element in the heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el;
        u32_t target_el;
        u32_t *found_el;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }
        target_el = buffer[rand() % 20];

        found_el = (u32_t *) bp_heap_find(&heap, &target_el, nullptr);

        REQUIRE(found_el != nullptr);
        REQUIRE(*found_el == target_el);
        REQUIRE(heap._coll._size == 20);
    }

    TEST_CASE("Find an element in the heap by its id")
    {
        bp_kv_t buffer[20] = {0};
        bp_heap_t heap     = BP_MAX_HEAP_INIT(buffer, bp_kv_cmp);
        bp_kv_t el;
        bp_kv_t target_el;
        bp_kv_t *found_el;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el.key   = rand() % 0x7fFFffFF;
            el.value = rand() % 0xffFF;
            bp_heap_push(&heap, &el);
        }
        target_el = buffer[rand() % 20];

        found_el = (bp_kv_t *) bp_heap_find(&heap, &target_el.key, bp_kv_key_cmp);

        REQUIRE(found_el != nullptr);
        REQUIRE(found_el->key == target_el.key);
        REQUIRE(found_el->value == target_el.value);
        REQUIRE(heap._coll._size == 20);
    }
}

TEST_SUITE("Max Heap | Error flow")
{
    TEST_CASE("Push an element on full heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el;
        int err;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el  = rand() % 0x7fFFffFF;
            err = bp_heap_push(&heap, &el);
        }
        el  = rand() % 0x7fFFffFF;
        err = bp_heap_push(&heap, &el);

        REQUIRE(err != 0);
    }

    TEST_CASE("Check top on the empty heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        u32_t *top_el;

        top_el = (u32_t *) bp_heap_top(&heap);

        REQUIRE(heap._coll._size == 0);
        REQUIRE(top_el == nullptr);
    }

    TEST_CASE("Pop element on the empty heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el         = 7;
        int err;

        err = bp_heap_pop(&heap, &el);

        REQUIRE(heap._coll._size == 0);
        REQUIRE(err != 0);
        REQUIRE(el == 7);
    }

    TEST_CASE("Delete an element at empty heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el         = 7;
        int err;

        err = bp_heap_del(&heap, &el, nullptr);

        REQUIRE(heap._coll._size == 0);
        REQUIRE(err != 0);
    }

    TEST_CASE("Delete an element at empty heap by its id")
    {
        bp_kv_t buffer[20] = {0};
        bp_heap_t heap     = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        bp_kv_t el         = {
            .key   = 7,
            .value = 10,
        };
        int err;

        err = bp_heap_del(&heap, &el.key, bp_kv_key_cmp);

        REQUIRE(heap._coll._size == 0);
        REQUIRE(err != 0);
    }

    TEST_CASE("Search a non existent element in the heap")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        u32_t el;
        u32_t *found_el;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        el = rand() % 0x7fFFffFF;
        for (int i = 0; i < 20; ++i) {
            if (el == buffer[i]) {
                el = rand() % 0x7fFFffFF;
                i  = -1;
            }
        }

        found_el = (u32_t *) bp_heap_find(&heap, &el, nullptr);

        REQUIRE(found_el == nullptr);
    }

    TEST_CASE("Search a non existent element in the heap by its id")
    {
        bp_kv_t buffer[20] = {0};
        bp_heap_t heap     = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        bp_kv_t el;
        bp_kv_t *found_el;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (int i = 0; i < 20; ++i) {
            el.key   = rand() % 0x7fFFffFF;
            el.value = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        el.key   = rand() % 0x7fFFffFF;
        el.value = rand() % 0x7fFFffFF;
        for (int i = 0; i < 20; ++i) {
            if (el.key == buffer[i].key) {
                el.key = rand() % 0x7fFFffFF;
                i      = -1;
            }
        }

        found_el = (bp_kv_t *) bp_heap_find(&heap, &el.key, bp_kv_key_cmp);

        REQUIRE(found_el == nullptr);
    }
}

TEST_SUITE("Max Heap | Invalid Parameters")
{
    TEST_CASE("Null heap argument in top function")
    {
        u32_t *el;

        el = (u32_t *) bp_heap_top(nullptr);

        REQUIRE(el == nullptr);
    }

    TEST_CASE("Null heap argument in clear function")
    {
        int err;

        err = bp_heap_clear(nullptr);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null heap argument in pop function")
    {
        int err;
        u32_t el = 7;

        err = bp_heap_pop(nullptr, &el);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null element argument in pop function")
    {
        int err;
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);

        err = bp_heap_pop(&heap, nullptr);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null heap argument in push function")
    {
        int err;
        u32_t el = 7;

        err = bp_heap_push(nullptr, &el);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null element argument in push function")
    {
        int err;
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);

        err = bp_heap_push(&heap, nullptr);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null heap argument in delete function")
    {
        int err;
        u32_t el = 7;

        err = bp_heap_del(nullptr, &el, nullptr);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null param argument in delete function")
    {
        int err;
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);

        err = bp_heap_del(&heap, nullptr, nullptr);

        REQUIRE(err != 0);
    }

    TEST_CASE("Null heap argument in find function")
    {
        u32_t *found_el;
        u32_t el = 7;

        found_el = (u32_t *) bp_heap_find(nullptr, &el, nullptr);

        REQUIRE(found_el == nullptr);
    }

    TEST_CASE("Null param argument in find function")
    {
        u32_t *found_el;
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);

        found_el = (u32_t *) bp_heap_find(&heap, nullptr, nullptr);

        REQUIRE(found_el == nullptr);
    }
}

TEST_SUITE("Max Heap | Iterator")
{
    TEST_CASE("BFS | Manual for")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        bp_iter it       = bp_heap_bfs_iter(&heap);
        u32_t el;
        int i;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        i = 0;
        for (u32_t *element = (u32_t *) it.init(&it); it.next(&it);
             element        = (u32_t *) it.get(&it)) {
            REQUIRE(buffer[i] == *element);
            i++;
        }
    }

    TEST_CASE("DFS | Manual for")
    {
        u32_t buffer[20]    = {0};
        usize lut_index[20] = {0, 1,  3,  7, 15, 16, 8,  17, 18, 4,
                               9, 19, 10, 2, 5,  11, 12, 6,  13, 14};
        bp_heap_t heap      = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        bp_iter it          = bp_heap_dfs_iter(&heap);
        u32_t el;
        int i;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        i = 0;
        for (u32_t *element = (u32_t *) it.init(&it); it.next(&it);
             element        = (u32_t *) it.get(&it)) {
            REQUIRE(buffer[lut_index[i]] == *element);
            i++;
        }
    }

    TEST_CASE("BFS | Foreach macro")
    {
        u32_t buffer[20] = {0};
        bp_heap_t heap   = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        bp_iter it       = bp_heap_bfs_iter(&heap);
        u32_t el;
        int i;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        i = 0;
        BP_FOREACH(u32_t, element, &it)
        {
            REQUIRE(buffer[i] == *element);
            i++;
        }
    }

    TEST_CASE("DFS | Foreach macro")
    {
        u32_t buffer[20]    = {0};
        usize lut_index[20] = {0, 1,  3,  7, 15, 16, 8,  17, 18, 4,
                               9, 19, 10, 2, 5,  11, 12, 6,  13, 14};
        bp_heap_t heap      = BP_MAX_HEAP_INIT(buffer, bp_int_cmp);
        bp_iter it          = bp_heap_dfs_iter(&heap);
        u32_t el;
        int i;
        unsigned int seed = time(NULL);

        printf("Test case \"%s\" seed: 0x%x\n", getCurrentTestName(), seed);
        srand(seed);

        for (i = 0; i < 20; ++i) {
            el = rand() % 0x7fFFffFF;
            bp_heap_push(&heap, &el);
        }

        i = 0;
        BP_FOREACH(u32_t, element, &it)
        {
            REQUIRE(buffer[lut_index[i]] == *element);
            i++;
        }
    }
}
