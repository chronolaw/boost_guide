// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#define BOOST_THREAD_VERSION 4
#include <boost/ref.hpp>
#include <boost/thread.hpp>
using namespace boost;

//////////////////////////////////////////

#include <boost/chrono.hpp>
using namespace boost::chrono;
seconds operator"" _s(unsigned long long n)
{
    return seconds(n);
}

milliseconds operator"" _ms(unsigned long long n)
{
    return milliseconds(n);
}
//////////////////////////////////////////

void case1()
{
    mutex mu;
    try
    {
        mu.lock();
        cout  << "some operations" << endl;
        mu.unlock();
    }
    catch (...)
    {
        mu.unlock();
    }

    {
        lock_guard<mutex> g(mu);
        cout  << "some operations" << endl;
    }
}

//////////////////////////////////////////
void case2()
{
    timed_mutex mu;

    auto flag = mu.try_lock_for(100_ms);
    if(flag)
    {
        cout << "lock timed mutex" << endl;
        mu.unlock();
    }

    {
        if(mu.try_lock_for(100_ms))
        {
            lock_guard<timed_mutex> g(mu, adopt_lock);
            cout << "lock timed mutex" << endl;
        }
    }
}

//////////////////////////////////////////
#include <boost/thread/lock_factories.hpp>

template <typename Lockable, typename D>
unique_lock<Lockable> my_make_lock(Lockable& mtx, D d)
{
    return unique_lock<Lockable> (mtx, d);
}

void case3()
{
    mutex mu;

    {
        auto g = make_unique_lock(mu);
        assert(g.owns_lock());
        cout  << "some operations" << endl;
    }

    {
        auto g = make_unique_lock(mu, defer_lock);
        assert(!g);

        assert(g.try_lock());
        assert(g);

        cout  << "some operations" << endl;
    }

    timed_mutex tm;
    //typedef unique_lock<timed_mutex> lock_type;

    {
        //lock_type g(tm, 100_ms);
        auto g = my_make_lock(tm, 100_ms);
        if(g)
        {
            cout << "lock timed mutex" << endl;
        }
    }

    auto g = make_unique_locks(mu, tm);
    assert(std::tuple_size<decltype(g)>::value == 2);
}

//////////////////////////////////////////
#include <boost/atomic.hpp>
#include <boost/thread/lockable_adapter.hpp>
class account final : public lockable_adapter<mutex>
{
private:
    atomic<int> m_money{0};
public:
    account() {}
    ~account() {}
public:
    int sum() const
    {
        return m_money;
    }

    void withdraw(int x)
    {
        m_money -= x;
    }

    void deposit(int x)
    {
        m_money += x;
    }
};

void case4()
{
    account a;

    {
        auto g = make_unique_lock(a);
        a.deposit(100);
        a.withdraw(20);
        assert(a.sum() == 80);
    }

    {
        auto b = make_unique_lock(a, try_to_lock);
        if(b)
        {
            a.withdraw(a.sum());
            assert(a.sum() == 0);
        }
    }
}

//////////////////////////////////////////
void case5()
{
    mutex m1, m2;

    {
        auto g1 = make_unique_lock(m1, adopt_lock);
        auto g2 = make_unique_lock(m2, adopt_lock);

        lock(m1, m2);
    }

    {
        auto g1 = make_unique_lock(m1, defer_lock);
        auto g2 = make_unique_lock(m2, defer_lock);

        try_lock(g1, g2);
    }
}

//////////////////////////////////////////
#include <boost/thread/lockable_concepts.hpp>
void case6()
{
    BOOST_CONCEPT_ASSERT((BasicLockable<mutex>));
    BOOST_CONCEPT_ASSERT((Lockable<mutex>));

    BOOST_CONCEPT_ASSERT((Lockable<timed_mutex>));
    BOOST_CONCEPT_ASSERT((TimedLockable<timed_mutex>));

    BOOST_CONCEPT_ASSERT((Lockable<account>));
    BOOST_CONCEPT_ASSERT((Lockable<lockable_adapter<mutex>>));

    //BOOST_CONCEPT_ASSERT((Lockable<atomic<int>>));
}

//////////////////////////////////////////
#include <boost/thread/shared_lock_guard.hpp>
class rw_data
{
    private:
        int m_x;
        shared_mutex rw_mu;
    public:
        rw_data():m_x(0){}
        void write()
        {
            unique_lock<shared_mutex> g(rw_mu);
            ++m_x;
        }
        void read(int *x)
        {
            //shared_lock_guard<shared_mutex> g(rw_mu);
            shared_lock<shared_mutex> g(rw_mu);
            *x = m_x;
        }
};

void writer(rw_data &d)
{
    for (int i = 0;i < 20; ++i)
    {
        this_thread::sleep_for(3_ms);
        d.write();
    }
}

void reader(rw_data &d)
{
    int x;
    for (int i = 0;i < 10; ++i)
    {
        this_thread::sleep_for(5_ms);
        d.read(&x);
        cout << "reader:"<< x << endl;
    }
}

void case7()
{
    rw_data d;
    thread_group pool;

    pool.create_thread(bind(writer,boost::ref(d)));
    pool.create_thread(bind(writer,boost::ref(d)));

    pool.create_thread(bind(reader,boost::ref(d)));
    pool.create_thread(bind(reader,boost::ref(d)));
    pool.create_thread(bind(reader,boost::ref(d)));
    pool.create_thread(bind(reader,boost::ref(d)));

    pool.join_all();
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
    case7();
}
