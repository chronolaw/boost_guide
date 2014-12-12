// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>
#include <boost/config/suffix.hpp>
using namespace boost;

//////////////////////////////////////////
void case1()
{
    cout << BOOST_STRINGIZE(__LINE__) << endl;
    cout << std::boolalpha << (string("22") == BOOST_STRINGIZE(__LINE__)) << endl;

    int x = 255;
    cout << BOOST_STRINGIZE(x) << endl;

    ignore_unused(x);
}

//////////////////////////////////////////

struct static_int
{
    BOOST_STATIC_CONSTANT(int, v1 = 10);
    BOOST_STATIC_CONSTANT(int, v2 = 20);
};

//////////////////////////////////////////

int main()
{
    case1();
}
