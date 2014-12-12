// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/smart_ptr.hpp>
using namespace boost;

//////////////////////////////////////////

struct counted_data
{
    // ...
    int m_count = 0;
    ~counted_data()
    {
        cout << "dtor" << endl;
    }
};

void intrusive_ptr_add_ref(counted_data* p)
{
    ++p->m_count;
}

void intrusive_ptr_release(counted_data* p)
{
    if(--p->m_count == 0)
    {
        delete p;
    }
}

//////////////////////////////////////////
#include <boost/smart_ptr/intrusive_ref_counter.hpp>

struct counted_data2 : public intrusive_ref_counter<counted_data2>
{
    ~counted_data2()
    {
        cout << "dtor2" << endl;
    }
};
//////////////////////////////////////////

int main()
{
    typedef intrusive_ptr<counted_data> counted_ptr;

    counted_ptr p(new counted_data);
    assert(p);
    assert(p->m_count == 1);

    counted_ptr p2(p);
    assert(p->m_count == 2);

    counted_ptr weak_p(p.get(), false);
    assert(weak_p->m_count == 2);

    p2.reset();
    assert(!p2);
    assert(p->m_count == 1);

    {
        typedef intrusive_ptr<counted_data2> counted_ptr;

        counted_ptr p(new counted_data2);
        assert(p);
        assert(p->use_count() == 1);

    }
}

