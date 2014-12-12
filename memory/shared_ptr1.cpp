// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
#include <exception>

#include <boost/smart_ptr.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    shared_ptr<int> spi(new int);
    assert(spi);
    *spi = 253;

    shared_ptr<std::string>  sps(new std::string("smart"));
    assert(sps->size() == 5);

    //shared_ptr<int> dont_do_this(new int[10]);
}

//////////////////////////////////////////

void case2()
{
    typedef shared_ptr<std::string> sp_t;
    std::map<sp_t, int> m;

    sp_t sp(new std::string("one"));
    m[sp] = 111;

    shared_ptr<std::exception> sp1(new std::bad_exception());

    auto sp2 = dynamic_pointer_cast<std::bad_exception>(sp1);
    auto sp3 = static_pointer_cast<std::exception>(sp2);
    assert(sp3 == sp1);
}

//////////////////////////////////////////

void case3()
{
    shared_ptr<int> sp(new int(10));
    assert(sp.unique());

    shared_ptr<int> sp2 = sp;

    assert(sp == sp2 &&
     sp.use_count() == 2);

    *sp2 = 100;
    assert(*sp == 100);

    sp.reset();
    assert(!sp);
}

//////////////////////////////////////////

class shared
{
private:
    shared_ptr<int> p;
public:
    shared(shared_ptr<int> p_):p(p_){}
    void print()
    {
        std::cout << "count:" << p.use_count()
            << " v=" <<*p << std::endl;
    }
};

void print_func(shared_ptr<int> p)
{
    std::cout << "count:" << p.use_count()
        << " v=" <<*p << std::endl;
}

void case4()
{
    shared_ptr<int> p(new int(100));
    shared s1(p), s2(p);

    s1.print();
    s2.print();

    *p = 20;
    print_func(p);

    s1.print();
}

//////////////////////////////////////////

void case5()
{
    auto sp = make_shared<std::string>("make_shared");
    auto spv = make_shared<std::vector<int> >(10, 2);
    assert(spv->size() == 10);
}

//////////////////////////////////////////

void case6()
{
    typedef std::vector<shared_ptr<int> > vs;
    vs v(10);

    int i = 0;
    for (auto pos = v.begin(); pos != v.end(); ++pos)
    {
        (*pos) = make_shared<int>(++i);
        std::cout << *(*pos) << ", ";
    }
    std::cout << std::endl;

    for (auto& ptr : v)
    {
        ptr = make_shared<int>(++i);
        std::cout << *ptr << ", ";
    }
    std::cout << std::endl;

    shared_ptr<int> p = v[9];
    *p = 100;
    std::cout << *v[9] << std::endl;
}

int main()
{
    case1();
    case2();
    case3();
    case4();
    case5();
    case6();
}
