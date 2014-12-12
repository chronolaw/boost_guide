// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/smart_ptr.hpp>
using namespace boost;

int main()
{
    int *p = new int[100];

    shared_array<int> sa(p);
    assert(sa.unique());

    shared_array<int> sa2 = sa;
    assert(sa2.use_count() == 2);

    sa[0] = 10;
    assert(sa2[0] == 10);
}

