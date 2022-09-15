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

TEST(HelloTest, BasicAssertions)
{
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);
}
