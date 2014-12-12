// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/algorithm/minmax_element.hpp>
//using namespace boost;

//////////////////////////////////////////

void case1()
{
    vector<int> v = {633, 90, 67,83, 2, 100};

    auto x = boost::minmax_element(v.begin(), v.end());
    cout << "min : " << *x.first << endl;
    cout << "max : "<< *x.second <<endl;

}

void case2()
{
    vector<int> v = {3,5,2,2,10,9,10,8};

    decltype(v.begin()) pos;
    pos = boost::first_min_element(v.begin(),v.end());
    assert(pos - v.begin() == 2);

    pos = boost::last_min_element(v.begin(),v.end());
    assert(pos - v.begin() == 3);

    auto x = boost::first_min_last_max_element(v.begin(),v.end());
    assert(x.first - v.begin() == 2 &&
            x.second - v.begin() == 6);

}

int main()
{
    case1();
    case2();
}
