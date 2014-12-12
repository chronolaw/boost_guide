// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr/make_unique.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    scoped_ptr<string> sp(new string("text"));

    assert(sp);
    assert(sp != nullptr);

    cout << *sp << endl;
    cout <<  sp->size() << endl;
}

//////////////////////////////////////////

struct posix_file
{
    posix_file(const char * file_name)
    {   cout << "open file:" << file_name << endl; }
    ~posix_file()
    {   cout << "close file" << endl;   }
};

void case2()
{
    scoped_ptr<posix_file> fp(new posix_file("/tmp/a.txt"));

    scoped_ptr<int> p(new int);

    if (p)
    {
        *p = 100;
        cout << *p << endl;
    }

    p.reset();

    assert(p == 0);
    if (!p)
    {   cout << "scoped_ptr == nullptr" << endl;   }

}

//////////////////////////////////////////

class ptr_owned final
{
    scoped_ptr<int> m_ptr;
};

void bad_case()
{
    scoped_ptr<string> sp(new string("text"));

    //sp++;
    //scoped_ptr<string> sp2 = sp;
    //std::prev(sp);
    //ptr_owned p;
    //ptr_owned p2(p);
}

//////////////////////////////////////////

void case_unique()
{
    auto p = boost::make_unique<int>(10);

    assert(p && *p == 10);

    p.release();
    assert(!p);

    auto a = boost::make_unique<int[]>(5);
    a[0] = 100;
    a[4] = 500;
    //a[5] = 1000;
}

//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case_unique();
}
