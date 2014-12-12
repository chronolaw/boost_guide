// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/static_assert.hpp>

//////////////////////////////////////////

void case1()
{
    BOOST_STATIC_ASSERT(2 == sizeof(short));
    BOOST_STATIC_ASSERT(true);
    BOOST_STATIC_ASSERT_MSG(16 == 0x10, "test static assert");
}

//////////////////////////////////////////

template<typename T>
T my_min(T a, T b)
{
    BOOST_STATIC_ASSERT_MSG(sizeof(T) < sizeof(int), "only short or char");
    return a < b? a: b;
}
void case2()
{
    cout << my_min((short)1, (short)3);
    //cout << my_min(1L, 3L);
}

//////////////////////////////////////////

namespace my_space
{
    class empty_class
    {
        BOOST_STATIC_ASSERT_MSG(sizeof(int)>=4, "for 32 bit");
    };

    BOOST_STATIC_ASSERT(sizeof(empty_class) == 1);
}


int main()
{
    case1();
    case2();
}

