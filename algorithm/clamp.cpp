// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/algorithm/clamp.hpp>
using namespace boost::algorithm;

//////////////////////////////////////////

void case1()
{
    assert(clamp(5, 1, 10) == 5);
    assert(clamp(5, 5, 10) == 5);
    assert(clamp(5, 1, 5) == 5);

    assert(clamp(5, 10, 15) == 10);
    assert(clamp(5, 0, 4) == 4);
}

//////////////////////////////////////////

void case2()
{
    vector<int> v = {2,4,6,8,10};

    clamp_range(v, ostream_iterator<int>(cout, ","), 3, 9);
}

int main()
{
    case1();
    case2();
}
