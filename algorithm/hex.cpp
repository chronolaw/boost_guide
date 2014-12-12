// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/algorithm/hex.hpp>
using namespace boost::algorithm;

//////////////////////////////////////////

void case1()
{
    string s;

    hex("123", ostream_iterator<char>(cout));
    cout << endl;

    hex("ABC", std::back_inserter(s));
    cout << s << endl;

    unhex(s, ostream_iterator<char>(cout));
    cout << endl;
}

//////////////////////////////////////////

void case2()
try
{
    //unhex("313", ostream_iterator<char>(cout));
    unhex("xyz", ostream_iterator<char>(cout));
}
catch(const boost::exception& e)
{
    cout << "unhex error" << endl;
}

int main()
{
    case1();
    case2();
}

