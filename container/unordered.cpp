// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/assign.hpp>
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
using namespace boost;


//////////////////////////////////////////
void case1()
{
    unordered_set<int > s = {1,2,3,4,5};

    for (auto x : s)
    {   cout << x << " ";   }
    cout << endl;
    cout << s.size() << endl;

    s.clear();
    cout << s.empty() << endl;

    s.insert(8);
    s.insert(45);
    cout << s.size() << endl;
    cout << *s.find(8) << endl;

    s.erase(45);

    using namespace boost::assign;
    unordered_set<int> us1 = list_of(1)(2)(3);
    unordered_set<int> us2 = list_of(3)(2)(1);
    assert(us1 == us2 );

}

//////////////////////////////////////////
void case2()
{
    typedef complex<double> complex_t;
    unordered_set<complex_t> s;

    s.emplace(1.0, 2.0);
    s.emplace(3.0, 4.0);

    for(auto& x : s)
    {    cout << x << ",";}
    cout << endl;

    s.emplace_hint(s.begin(), 5.0, 6.0);
    for(auto& x : s)
    {    cout << x << ",";}

}


//////////////////////////////////////////
void case3()
{
    using namespace boost::assign;

    unordered_map<int, string> um =
        map_list_of(1,"one")(2, "two")(3, "three");

    um.insert(make_pair(10,"ten"));
    cout << um[10] << endl;
    um[11] = "eleven";
    um[15] = "fifteen";

    auto p = um.begin();
    for (; p != um.end(); ++p)
    {   cout << p->first << "-" << p->second << ",";    }
    cout << endl;

    um.erase(11);
    cout << um.size() << endl;

    unordered_map<int, string> um1 = map_list_of(1,"11")(2,"22");
    unordered_map<int, string> um2 = map_list_of(1,"one")(2,"two");
    assert(um1 != um2);

}

//////////////////////////////////////////
void case4()
{
    typedef complex<double> complex_t;
    typedef unordered_map<int,complex_t> um_t;
    um_t s;

    s.emplace(boost::unordered::piecewise_construct,
        make_tuple(1),make_tuple(1.0, 2.0));
    s.emplace(boost::unordered::piecewise_construct,
        make_tuple(3),make_tuple(3.0, 4.0));

    for(auto& x: s)
    {
            cout << x.first << "<->" << x.second << ",";
    }
    cout << endl;

    s.emplace_hint(s.begin(),
    boost::unordered::piecewise_construct,
        make_tuple(5),make_tuple(5.0, 6.0));
    for(auto& x: s)
    {
            cout << x.first << "<->" << x.second << ",";
    }

}

//////////////////////////////////////////
void case5()
{
    using namespace boost::assign;

    unordered_set<int> us = (list_of(1),2,3,4);
    cout << us.bucket_count() << endl;

    for (size_t i = 0; i < us.bucket_count(); ++i)
    {   cout << us.bucket_size(i) << ",";   }

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
