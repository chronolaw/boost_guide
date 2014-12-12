// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/timer.hpp>
using namespace boost;

//////////////////////////////////////////

int main()
{
    timer t;

    cout << CLOCKS_PER_SEC << endl;
    cout << "max timespan:"
        << t.elapsed_max() /3600 << "h" <<endl;
    cout << "min timespan:"
        << t.elapsed_min() << "s" << endl;
    cout << "now time elapsed:"
        << t.elapsed() <<"s" << endl;
}

