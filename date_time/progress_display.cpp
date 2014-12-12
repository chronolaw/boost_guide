// Copyright (c) 2015
// Author: Chrono Law
#include <fstream>
#include <std.hpp>
using namespace std;

#include <boost/progress.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    vector<string> v(100);
    ofstream fs("./test.txt");

    //progress_display pd(v.size(),cout ,"%%%", "+++", "???");
    progress_display pd(v.size());

    for (auto& x : v)
    {
        fs << x << endl;
        ++pd;
    }
}

//////////////////////////////////////////

void case2()
{
    vector<string> v(100, "aaa");

    v[10] = "";v[23] = "";
    ofstream fs("./test.txt");
    progress_display pd(v.size());

    for (auto pos = v.begin(); pos != v.end();++pos)
    {
        fs << *pos << endl;
        ++pd;
        if (pos->empty())
        {
            cout << "null string # " 
                << (pos - v.begin())<< endl;
        }
    }
}

//////////////////////////////////////////

int main()
{
    case1();
    case2();
}


