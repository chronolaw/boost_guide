// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/format.hpp>
#include <boost/test/minimal.hpp>

int test_main( int argc, char* argv[] )
{
    using namespace boost;
    format fmt("%d-%d");

    BOOST_CHECK(fmt.size() != 0);
    fmt % 12 % 34;
    BOOST_REQUIRE(fmt.str() == "12-34");

    //BOOST_ERROR("演示一条错误消息");

    fmt.clear();
    fmt % 12;
    try
    {
        std::cout << fmt;
    }
    catch (...)
    {
        //BOOST_FAIL("致命错误，测试终止");
    }
    return 0;
}

