// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/utility/result_of.hpp>
using namespace boost;

//////////////////////////////////////////

template<typename F, typename T>
typename boost::result_of<F(T)>::type call_func(F f, T t)
{   return f(t);}


void case1()
{
    typedef double (*Func)(double d);
    Func func = sqrt;

    boost::result_of<Func(double)>::type x = func(5.0);
    cout << typeid(x).name() << endl;

    auto y =  call_func(func, 5.0);
    cout << typeid(y).name() << endl;

}

int main()
{
    case1();
}


