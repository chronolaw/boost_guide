// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/algorithm/minmax.hpp>
//using namespace boost;

//////////////////////////////////////////

void case1()
{
    std::cout << std::min(200, 12) << std::endl;
    std::cout << std::max(200, 12) << std::endl;

    auto x = boost::minmax(1, 2);
    std::cout << boost::get<0>(x) << " " << boost::get<1>(x);
    std::cout << std::endl;

}

//////////////////////////////////////////

void case2()
{
    std::string s1("5000"), s2("123");

    //auto xx = boost::minmax(s1, s2);
    auto x = std::minmax(s1, s2) ;
    cout << get<0>(x) << " " << get<1>(x) << endl;

    auto y = std::minmax({3,4,8,1}) ;
    cout << get<0>(y) << " " << get<1>(y);

}

int main()
{
    case1();
    case2();
}
