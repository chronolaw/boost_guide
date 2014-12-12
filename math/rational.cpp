// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
#include <type_traits>
using namespace std;

//////////////////////////////////////////

#include <boost/rational.hpp>
using namespace boost;

void case1()
{
    rational<int> a;
    rational<int> b(20);
    rational<int> c(31415, 10000);

    rational<int> r;
    r = 0x31;
    r.assign(7, 8);
}

//////////////////////////////////////////

void case2()
{
    rational<int> r(1.0);
    cout << r << endl;

    r = 3.14;
    cout << r << endl;

    r.assign(7.23, 100);
    cout << r << endl;
}

//////////////////////////////////////////

void case3()
{
    rational<int>   a(3),b(65534),c(22,7);

    b += a;
    c -= a;
    if (c >= 0)
    {
        c = c * b;
        ++a;
    }
    assert(a == 4);
}

//////////////////////////////////////////

void case4()
{
    rational<int> r(10);
    if (r)
    {
        r -= 10;
    }
    assert(!r);
}

//////////////////////////////////////////

void case5()
{
    rational<int> r(2718, 1000);
    cout << rational_cast<int>(r) << endl;
    cout << rational_cast<double>(r) << endl;

    //double x = r;
}

//////////////////////////////////////////

void case6()
{
    rational<int> r(22,7);
    cout << r.numerator() << ":" << r.denominator()
          << "=" << rational_cast<double>(r);
    cout << endl;
}

//////////////////////////////////////////

void case7()
{
    rational<int> a(-1414,1000), pi(314, 100);

    cout << "abs=" << abs(a) << endl;
    cout << pow(rational_cast<double>(a), 2) << endl;
    cout << cos(rational_cast<double>(pi)) << endl;

}

//////////////////////////////////////////
#include <boost/format.hpp>

void case8()
{
    int a = 37, b = 62;
    format fmt("gcd(%1%, %2%) = %3%. lcm(%1%, %2%) = %4%\n");
    cout << fmt % a % b % gcd(a,b) % lcm(a,b);
}

int main()
{
    case1();
    case2();
    case3();
    case4();
    case5();
    case6();
    case7();
    case8();
}

