// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/assign.hpp>
#include <boost/circular_buffer.hpp>
using namespace boost;

//////////////////////////////////////////
void case1()
{
    circular_buffer<int> cb(5);
    assert(cb.empty());

    cb.push_back(1);
    cb.push_front(2);
    assert(cb.front() == 2);
    cb.insert(cb.begin(), 3);


    for (auto pos = cb.begin(); pos != cb.end();++pos)
    {   cout << *pos << ",";    }
    cout << endl;

    cb.pop_front();
    assert(cb.size() == 2);
    cb.push_back();
    assert(cb[0] = 2);

    //using namespace boost::assign;
    circular_buffer<int> cb1 = (assign::list_of(1),2,3);
    circular_buffer<int> cb2 = (assign::list_of(3),4,5);
    circular_buffer<int> cb3 = cb1;

    assert(cb1 < cb2);
    assert(cb1 == cb3);

}

//////////////////////////////////////////
template<typename T>
void print(T& cb)
{
    for (auto& x: cb)
    {   cout << x << ",";   }
    cout << endl;
}

void case2()
{
    circular_buffer<int> cb = (assign::list_of(1),2,3);
    print(cb);

    cb.push_back(4);
    print(cb);

    cb.push_back(5);
    print(cb);

    cb.pop_front();
    print(cb);

}

//////////////////////////////////////////
void case3()
{
    circular_buffer<int> cb =(assign::list_of(1),2,3,4,5);

    assert(cb.full());
    print(cb);

    int *p = cb.linearize();
    assert(p[0]== 1 && p[3] == 4);

    cb.rotate(cb.begin()+ 2);
    print(cb);

}

//////////////////////////////////////////
void case4()
{
    using namespace boost::assign;

    circular_buffer_space_optimized<int> cb( 10);
    push_back(cb)(1),2,3,4;

    assert(cb.size() == 4);
    assert(cb.capacity() == 10);

    cb.resize(100, 10);
    assert(cb.size() == cb.capacity());

}


//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
    case4();
}
