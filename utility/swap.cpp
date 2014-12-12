// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/swap.hpp>
#include <boost/assign.hpp>

//////////////////////////////////////////
void case1()
{
    using namespace boost::assign;

    int a1[10];
    int a2[10];

    std::fill_n(a1, 10, 5);
    std::fill_n(a2, 10, 20);

    boost::swap(a1, a2);

}

//////////////////////////////////////////
class point
{
    int x, y, z;
public:
    explicit point(int a=0, int b=0, int c=0):x(a),y(b),z(c){}

    void print()const
    {       cout << x <<","<< y <<","<< z << endl;  }

    void swap(point &p)
    {
        std::swap(x, p.x);
        std::swap(y, p.y);
        std::swap(z, p.z);
        cout << "inner swap" << endl;
    }
};

//namespace std
//{
//template<>
//void swap(point &x, point &y)               //模板特化swap函数
//{   x.swap(y);}
//}

namespace boost {
void swap(point &x, point &y)
{   x.swap(y);}
}

void case2()
{
    point a(1,2,3), b(4,5,6);

    cout << "std::swap" << endl;
    std::swap(a,b);

    cout << "boost::swap" << endl;
    boost::swap(a, b);
}


//////////////////////////////////////////

int main()
{
    case1();
    case2();
}
