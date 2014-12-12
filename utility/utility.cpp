// Copyright (c) 2015
// Author: Chrono Law
#include <bitset>
#include <std.hpp>
using namespace std;

#include <boost/utility.hpp>

//////////////////////////////////////////
void case1()
{
    cout << hex << showbase;
    cout <<  BOOST_BINARY(0110) << endl;
    cout <<  BOOST_BINARY(0110 1101) << endl;
    cout <<  BOOST_BINARY(10110110 01) << endl;
    cout <<  bitset<5>(BOOST_BINARY(0110)) << endl;

    cout <<  BOOST_BINARY_UL(101 1001) << endl;
    long long x = BOOST_BINARY_LL(1101);
    cout << x << endl;

}

//////////////////////////////////////////
#include <boost/current_function.hpp>

double func()
{
      cout << BOOST_CURRENT_FUNCTION << endl;
        return 0.0;
}

string str = BOOST_CURRENT_FUNCTION;      //错误用法，不能用在函数作用域外

void case2()
{
    cout << str << endl;
    cout << __FUNCTION__ << endl;
    cout << BOOST_CURRENT_FUNCTION << endl;
    func();
}



//////////////////////////////////////////

int main()
{
    case1();
    case2();
}
