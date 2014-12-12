// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
//using namespace std;

#include <boost/bind.hpp>
#include <boost/function.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    function<int()> func, func1;
    function<int (int  , int  , int   )>    func2;

    //func == func1;

    assert(func.empty());
    assert(!func);

    function0<int> func0;
    func0.clear();
    assert(!func0);
}

//////////////////////////////////////////

int f(int a, int b)
{   return a + b;}

void case2()
{
    //function<int(int,int)> func;
    function<decltype(f)> func;
    assert(!func);

    func = f;
    assert(func.contains(&f));

    if (func)
    {
        std::cout << func(10, 20);
    }

    func = 0;
    assert(func.empty());
}

//////////////////////////////////////////

struct demo_class
{
    int add(int a, int b)
    {       return a + b;   }
    int operator()(int x) const
    {       return x*x; }
};

void case3()
{
    function<int(demo_class&, int,int)> func1;

    func1 = bind(&demo_class::add, _1, _2, _3);

    demo_class sc;
    std::cout << func1(sc, 10, 20);

    function<int(int,int)> func2;

    func2 = bind(&demo_class::add,&sc, _1, _2);
    std::cout << func2(10, 20);

}

//////////////////////////////////////////

void case4()
{
    demo_class sc;
    function<int(int)> func;

    func = cref(sc);
    std::cout << func(10);
}

//////////////////////////////////////////

template<typename T>
struct summary
{
    typedef void result_type;
    T sum;

    summary(T v = T()):sum(v){}

    void operator()(T const &x)
    {   sum += x;   }
};

void case5()
{
    std::vector<int> v = {1,3,5,7,9};

    summary<int> s;
    function<void(int const&)> func(ref(s));

    std::for_each(v.begin(), v.end(), func);
    std::cout << s.sum << std::endl;
}

//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
    case4();
    case5();
}


