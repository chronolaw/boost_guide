// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
//using namespace std;

#include <boost/bind.hpp>
using namespace boost;

//////////////////////////////////////////

int f(int a, int b)
{   return a + b;}

int g(int a, int b, int c)
{   return a + b * c;}

//typedef int (*f_type)(int, int);
//typedef int (*g_type)(int, int, int);
typedef decltype(&f) f_type;
typedef decltype(&g) g_type;

void case1()
{
    std::cout << bind(f,1,2)() << std::endl;
    std::cout << bind(g,1,2,3)() << std::endl;

    //f_type fp = f;
    //std::cout << bind(fp, _1, _2)(1,2) << std::endl;

    int x = 1, y = 2, z = 3;

    bind(f, _1,  9)(x) ;
    bind(f, _1, _2)(x, y) ;
    bind(f, _2, _1)(x, y) ;
    bind(f, _1, _1)(x, y) ;
    bind(g, _1, 8, _2)(x, y) ;
    bind(g, _3, _2, _2)(x, y, z) ;

    f_type pf = f;
    g_type pg = g;

    std::cout << bind(pf, _1, 9)(x) << std::endl;
    std::cout << bind(pg, _3, _2, _2)(x, y, z) << std::endl;

}

//////////////////////////////////////////

struct demo
{
    int f(int a, int b)
    {   return a + b;   }
};

struct point
{
    int x, y;
    point(int a = 0, int b = 0):x(a),y(b){}
    void print()
    {   std::cout << "(" << x << "," << y << ")\n";  }
};


void case2()
{
    demo a,&ra=a;
    demo *p = &a;

    std::cout << bind(&demo::f, a, _1, 20)(10) << std::endl;
    std::cout << bind(&demo::f, ra, _2, _1)(10, 20) << std::endl;
    std::cout << bind(&demo::f, p, _1, _2)(10, 20) << std::endl;

    std::vector<point> v(10);
    std::for_each(v.begin(), v.end(), bind(&point::print, _1));
}

//////////////////////////////////////////

void case3()
{
    std::vector<point> v(10);
    std::vector<int> v2(10);

    std::transform(v.begin(), v.end(), v2.begin(), bind(&point::x, _1));

    for(auto x : v2)                        //foreach循环输出值
        std::cout << x << ",";

    typedef std::pair<int, std::string> pair_t;
    pair_t p(123, "string");

    std::cout << bind(&pair_t::first , p)() << std::endl;
    std::cout << bind(&pair_t::second, p)() << std::endl;

}

//////////////////////////////////////////

struct func
{
        int operator()(int a, int b)
            {   return a + b;   }
};

void case4()
{
    bind(std::greater<int>(), _1, 10);
    bind(std::plus<int>(), _1, _2);
    bind(std::modulus<int>(), _1, 3);

    std::cout << bind<int>(func(), _1, _2)(10,20) << std::endl;
}

//////////////////////////////////////////

void case5()
{
    int x = 10;
    std::cout << bind(g,_1, cref(x), ref(x))(10) << std::endl;

    func af;
    std::cout << bind<int>(ref(af), _1, _2)(10, 20) << std::endl;


}

//////////////////////////////////////////

void case6()
{
    int x = 10;
    auto r = ref(x);
    {
        int *y = new int(20);
        r = ref(*y);

        std::cout << r << std::endl;
        std::cout << bind(g, r, 1, 1)() << std::endl;
        delete y;
    }
    std::cout << bind(g, r, 1, 1)() << std::endl;
}

//////////////////////////////////////////

#include <boost/rational.hpp>

void case7()
{
    typedef rational<int> ri;
    std::vector<ri> v = {ri(1,2),ri(3,4),ri(5,6)};


    std::remove_if(v.begin(), v.end(), bind(&ri::numerator, _1) == 1 );
    assert(v[0].numerator() == 3);


    assert(std::find_if(v.begin(), v.end(), bind(&ri::numerator, _1) == 1) == v.end());

    auto pos = std::find_if(v.begin(), v.end(),
            bind(&ri::numerator, _1) >3 && bind(&ri::denominator, _1) < 8);

    std::cout << *pos << std::endl;

    pos = find_if(v.begin(), v.end(),
            [](ri &r)
            {
                return r.numerator() >3 && r.denominator() < 8;
            });
    std::cout << *pos << std::endl;
}

//////////////////////////////////////////

void case8()
{
    auto lf = [](int x)
    {
        return f(x, 9);
    };

    assert(lf(10) == bind(f, _1, 9)(10));
}

//////////////////////////////////////////

int f(double a, double b)
{   return a * b;}

typedef int (*f_type1)(int, int);
typedef int (*f_type2)(double, double);

void case9()
{
    //std::cout << bind(f,1,2)() << std::endl;

    f_type1 pf1 = f;
    f_type2 pf2 = f;

    std::cout << bind(pf1,1,2)() << std::endl;
    std::cout << bind(pf2,1,2)() << std::endl;
}

//////////////////////////////////////////

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
    case9();
}


