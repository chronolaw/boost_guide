// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#define BOOST_RATIO_EXTENSIONS
#include <boost/ratio.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    typedef ratio<1, 2> half;

    assert(half::num == 1);
    assert(half::den == 2);

    auto v = half::value();
    cout << v << endl;
    assert(v * 2 == 1);

    half frac;
    assert(frac().numerator() == frac.num);

    typedef ratio<2, 4> two_fourth;
    cout << two_fourth()() << endl;
    assert(half::value() == two_fourth::value());

    typedef ratio<12> dozen;
    assert(2* dozen()() == 24);
}

//////////////////////////////////////////
typedef ratio<1, 2> half;
typedef ratio<1, 4> quater;

typedef ratio<12, 1> dozen;
typedef ratio<kilo::num*10, 1> cn_wan;

void case2()
{
    assert(kilo::num < kibi::num);
    cout << kilo::num << endl;
    cout << kibi::num << endl;

    assert((quater())()*2 == half()());
    assert((mega())() == cn_wan()()*100);
}

//////////////////////////////////////////
boost::intmax_t operator"" _kb(unsigned long long n)
{
    return n * boost::kibi::num;
}

boost::intmax_t operator"" _gb(unsigned long long n)
{
    return n * boost::gibi::num;
}

void case3()
{
    auto x = 2_gb;
    auto y = 10_kb;

    assert(x = 2 * 100 * y);
}

//////////////////////////////////////////
template<typename R>
using string_out = ratio_string<R, char>;

void case4()
{
    cout << string_out<kilo>::prefix() << endl;
    cout << string_out<kilo>::symbol() << endl;

    cout << string_out<nano>::prefix() << endl;
    cout << string_out<nano>::symbol() << endl;

    cout << string_out<ratio<22, 7>>::prefix() << endl;
}

//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
    case4();
}
