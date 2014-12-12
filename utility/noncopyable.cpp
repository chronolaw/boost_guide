// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/noncopyable.hpp>

//////////////////////////////////////////
class do_not_copy: boost::noncopyable
{};

//////////////////////////////////////////


int main()
{
    do_not_copy d1;
    //do_not_copy d2(d1);
    //do_not_copy d3;
    //d3 = d1;
}

