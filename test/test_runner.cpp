/**
 * @file test_runner.cpp
 * @author Matheus T. dos Santos (tenoriomatheus0@gmail.com)
 * @brief
 * @version 0.1.0
 * @date 26/09/2021
 *
 * @copyright Matheus T. dos Santos todos os direitos reservados (c) 2021
 *
 */
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

const char* getCurrentTestName()
{
    return doctest::detail::g_cs->currentTest->m_name;
}

int main(int argc, char** argv)
{
    doctest::Context context;
    int err;

    context.applyCommandLine(argc, argv);
    err = context.run();

    return err;
}