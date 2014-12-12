// Copyright (c) 2015
// Author: Chrono Law
//#include <std.hpp>
//using namespace std;

#include <boost/core/ignore_unused.hpp>
using namespace boost;

//////////////////////////////////////////
int func(int x, int y)
{
    int i;

    ignore_unused(x, i);

    return y;
}

//////////////////////////////////////////
void func2()
{
    typedef int result_type;
    ignore_unused<result_type>();
}


int main()
{
    //func(1, 2);
}


