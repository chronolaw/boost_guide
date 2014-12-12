// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>

#define BOOST_SYSTEM_NO_DEPRECATED
#define BOOST_POOL_NO_MT
#include <boost/pool/pool.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    pool<> pl(sizeof(int));

    int *p = static_cast<int*>(pl.malloc());
    assert(pl.is_from(p));

    pl.free(p);
    for (int i = 0;i < 100; ++i)
    {   pl.ordered_malloc(10);  }
}

//////////////////////////////////////////

#include <boost/pool/object_pool.hpp>

struct demo_class
{
public:
    int a,b,c;
    demo_class(int x = 1, int y = 2, int z = 3):
        a(x),b(y),c(z){}
};

void case2()
{
    object_pool<demo_class> pl;

    auto p = pl.malloc();
    assert(pl.is_from(p));

    assert(p->a!=1 || p->b != 2 || p->c !=3);

    p = pl.construct(7, 8, 9);
    assert(p->a == 7);

    object_pool<string> pls;
    for (int i = 0; i < 10 ; ++i)
    {
        string *ps = pls.construct("hello object_pool");
        cout << *ps << endl;
    }
}

//////////////////////////////////////////

template<typename P, typename ... Args>
inline typename P::element_type*
construct(P& p, Args&& ... args)
{
    typename P::element_type* mem = p.malloc();
    assert(mem != 0);
    new (mem) typename P::element_type(
                std::forward<Args>(args)...);
    return mem;
}

struct demo_class2
{
    demo_class2(int, int, int, int)
    {   cout << "demo_class ctor" << endl;}
    ~demo_class2()
    {   cout << "demo_class dtor" << endl;}
};

void case3()
{
    object_pool<demo_class2> pl;
    auto d = construct(pl, 1,2,3,4);

    boost::ignore_unused(d);
}

//////////////////////////////////////////

#include <boost/pool/singleton_pool.hpp>

struct pool_tag{};
typedef singleton_pool<pool_tag, sizeof(int)> spl;

void case4()
{
    int *p = (int *)spl::malloc();
    assert(spl::is_from(p));
    spl::release_memory();
}

//////////////////////////////////////////

#include <boost/pool/pool_alloc.hpp>

void case5()
{
    vector<int, pool_allocator<int> > v;

    v.push_back(10);
    cout << v.size();
}

int main()
{
    case1();
    case2();
    case3();
    case4();
    case5();
}
