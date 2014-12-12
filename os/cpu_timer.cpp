// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/algorithm/string.hpp>
#include <boost/timer/timer.hpp>
using namespace boost::timer;

//////////////////////////////////////////
void case1()
{
    vector<string> v(10, "monado");

    cpu_timer t;
    assert(!t.is_stopped());

    for (int i = 0;i < 10000; ++i)
    {
        boost::join(v, "-");
    }//end for

    t.stop();
    assert(t.is_stopped());

    cout << "pause for a while..." << endl;
    cout << "we can do something..." << endl;

    t.resume();
    assert(!t.is_stopped());

    for(string& x : v)
    {   x +=x; }

    cout << t.format();
}

//////////////////////////////////////////
void case2()
{
    const nanosecond_type ms = 1000 * 1000;

    cpu_times ct = {2000 *ms, 1000*ms, 100*ms};
    cout << format(ct, 7);
}

//////////////////////////////////////////
void case3()
{
    cpu_times ct = {2000, 1000, 100 };
    cout << format(ct, 3);

}

//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
}

