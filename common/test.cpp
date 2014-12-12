// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/version.hpp>
#include <boost/config.hpp>

int main()
{
    cout << __cplusplus << endl;
    cout << BOOST_VERSION << endl;
    cout << BOOST_LIB_VERSION<< endl;

    cout << BOOST_PLATFORM << endl;
    cout << BOOST_COMPILER << endl;
    cout << BOOST_STDLIB << endl;
}
