// Copyright (c) 2015
// Author: Chrono Law
#include <sstream>
#include <std.hpp>
using namespace std;

#include <boost/progress.hpp>
using namespace boost;

//////////////////////////////////////////

int main()
{
    {
        boost::progress_timer t;

    }
    {
        boost::progress_timer t;
    }

    stringstream ss;
    {
        progress_timer t(ss);
    }
    cout << ss.str();
}


