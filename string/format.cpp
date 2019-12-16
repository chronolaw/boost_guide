// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/format.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    cout << format("%s:%d+%d=%d\n") %"sum" % 1 % 2 % (1+2);

    format fmt("(%1% + %2%) * %2% = %3%\n");
    fmt % 2 % 5 ;
    fmt % ((2+5)*5);
    cout << fmt.str();
}

//////////////////////////////////////////

void case2()
{
    format fmt("%05d\t%-8.3f\t% 10s\t%05X\n");
    cout << fmt %62 % 2.236 % "123456789" % 48;

    format fmt2("%|05d|\t%|-8.3f|\t%| 10s|\t%|05X|\n");
    cout << fmt2 %62 % 2.236 % "123456789" % 48;

    const format fmt3("%10d %020.8f %010X %10.5e\n");
    cout << format(fmt3) %62 % 2.236 % 255 % 0.618;
}

//////////////////////////////////////////
#include <iomanip>
using namespace boost;
using boost::io::group;

void case3()
{
    format fmt("%1% %2% %3% %2% %1% \n");
    cout << fmt %1 % 2 % 3;

    fmt.bind_arg(2, 10);
    cout << fmt %1 %3;

    fmt.clear();

    cout << fmt % group(showbase,oct,  111) % 333;

    fmt.clear_binds();


    fmt.modify_item(1, group(hex, right, showbase,setw(8), setfill('*')));
    cout << fmt % 49 % 20 % 100;
}


//////////////////////////////////////////


int main()
{
    case1();
    case2();
    case3();
}

