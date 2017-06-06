// Copyright (c) 2017
// Author: Chrono Law
//#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE decorator_test
#include <boost/test/unit_test.hpp>

namespace utf = boost::unit_test;


BOOST_TEST_DECORATOR(*utf::description("a decorator test demo"))
BOOST_AUTO_TEST_SUITE(s_decorator, * utf::label("decorator"))

BOOST_AUTO_TEST_CASE(t_case1,
                     *utf::label("low")
                     *utf::description("a normal test case"))
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(t_case2,
                     *utf::label("low"))
{
    BOOST_CHECK(true);
}

BOOST_TEST_DECORATOR(*utf::label("high"))
BOOST_AUTO_TEST_CASE(t_case3)
{
    BOOST_REQUIRE_GE(2, 1);
}

BOOST_AUTO_TEST_SUITE_END()

