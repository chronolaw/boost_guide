// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/atomic.hpp>
using namespace boost;

//////////////////////////////////////////
void case1()
{
    atomic<int> a(10);
    assert(a == 10);

    atomic<long> l;
    l = 100L;
    cout << l << endl;

    atomic<double> d(2.414);
    cout << d << endl;
}

//////////////////////////////////////////
void case2()
{
    atomic<bool> b{false};
    assert(!b.load());

    b.store(true);
    assert(b);

    atomic<int> n(100);
    assert(n.exchange(200) == 100);
    assert(n == 200);
}
//////////////////////////////////////////
void case3()
{
    atomic<long> l(100);

    long v = 100;
    if (l.compare_exchange_weak(v, 313))
    {
        assert(l == 313 && v == 100);
    }

    v = 200;
    auto b = l.compare_exchange_strong(v, 99);
    assert(!b && v == 313);

    l.compare_exchange_weak(v, 99);
    assert(l == 99 && v == 313 );
}

//////////////////////////////////////////
#include <boost/utility.hpp>
void case4()
{
    atomic<int> n(100);

    assert(n.fetch_add(10) == 100);
    assert(n == 110);

    assert(++n == 111);
    assert(n++ ==111);
    assert(n == 112);

    assert((n -= 10) == 102);

    atomic<int> b{BOOST_BINARY(1101)};

    auto x = b.fetch_and(BOOST_BINARY(0110));
    assert(x == BOOST_BINARY(1101) &&
           b == BOOST_BINARY(0100));
    assert((b |= BOOST_BINARY(1001))
            == BOOST_BINARY(1101));
}

//////////////////////////////////////////
void case5()
{
    atomic<bool> b{true};
    assert(b);

    b = false;
    assert(!b.load());

    auto x = b.exchange(true);
    assert(b && !x);
}
//////////////////////////////////////////
#include <boost/intrusive_ptr.hpp>

template<typename T>
class ref_count
{
private:
    typedef boost::atomic<int> atomic_type;
    mutable atomic_type m_count{0};
protected:
    ref_count() {}
    ~ref_count() {}
public:
    typedef boost::intrusive_ptr<T> counted_ptr;
    void add_ref() const
    {
        m_count.fetch_add(1, boost::memory_order_relaxed);
    }

    void sub_ref() const
    {
        if (m_count.fetch_sub(1, boost::memory_order_release) == 1)
        {
            boost::atomic_thread_fence(boost::memory_order_acquire);
            delete static_cast<const T*>(this);
        }
    }

    decltype(m_count.load()) count() const
    {
        return m_count.load();
    }

public:
    template<typename ... Args>
    static counted_ptr make_ptr(Args&& ... args)
    {
        return counted_ptr(new T(std::forward<Args>(args)...));
    }
private:
    friend void intrusive_ptr_add_ref(const T* p)
    {
        p->add_ref();
    }
    friend void intrusive_ptr_release(const T* p)
    {
        p->sub_ref();
    }
};

class demo: public ref_count<demo>
{
public:
    demo()
    {
        cout << "demo ctor" << endl;
    }
    ~demo()
    {
        cout << "demo dtor" << endl;
    }
    int x;
};
void case6()
{
    //demo::counted_ptr p(new demo);
    auto p = demo::make_ptr();

    p->x = 10;
    assert(p->x == 10);
    assert(p->count() == 1);
}
//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
    case4();
    case5();
    case6();
}
