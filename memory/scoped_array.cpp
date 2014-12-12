// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/smart_ptr.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    int *arr = new int[100];
    scoped_array<int> sa(arr);

    fill_n(&sa[0],100, 5);
    sa[10] = sa[20] + sa[30];
}

//////////////////////////////////////////

void case2()
{
    unique_ptr<int[]> up(new int[10]);

    assert(up);
    up[0] = 10;
    cout << up[0] << endl;

    up.reset();
    assert(!up);
}

//////////////////////////////////////////

int main()
{
    case1();
    case2();
}
