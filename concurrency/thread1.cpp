// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

//#define BOOST_THREAD_VERSION 4
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
    {
        thread t1;
        assert(!t1.joinable());

        thread t2([]{cout << "a thread" << endl;});
        assert(t2.joinable());

    }

    thread t1,t2;
    cout << t1.get_id() << endl;
    assert(t1.get_id() == t2.get_id());

    cout << thread::hardware_concurrency() << endl;
    cout << thread::physical_concurrency() << endl;

}

//////////////////////////////////////////
#include <boost/bind.hpp>
void dummy(int n)
{
    for(int i = 0;i < n; ++i);
    cout << n << endl;
}

void case2()
{
    //thread t1(dummy, 100);
    //thread t2(dummy, 500);

    thread t1(bind(dummy, 100));
    thread t2([]{dummy(500);});

    //this_thread::sleep_for(200_ms);
    t1.try_join_for(100_ms);
    t2.join();
}

//////////////////////////////////////////
void case3()
{
    thread t1(dummy, 100);
    t1.detach();
    assert(!t1.joinable());

    thread(dummy, 1000).detach();
    this_thread::sleep_for(200_ms);
}

//////////////////////////////////////////
#include <boost/thread/thread_guard.hpp>
#include <boost/thread/scoped_thread.hpp>
void case4()
{
    thread t1(dummy, 200);
    thread t2(dummy, 300);

    thread_guard<detach> g1(t1);
    thread_guard<>       g2(t2);

    {
        scoped_thread<detach> t1(dummy, 10);
        scoped_thread<>       t2(dummy, 20);
    }

    this_thread::sleep_for(100_ms);
}

//////////////////////////////////////////
void to_interrupt(int x)
try
{
    for (int i = 0;i < x; ++i)
    {
        //this_thread::sleep_for(400_ms);
        cout << i << endl;
        this_thread::interruption_point();
    }
}
catch(const thread_interrupted& )
{
    cout << "thread_interrupted" << endl;
}

void case5()
{
    thread t(to_interrupt,10);
    //this_thread::sleep_for(1_s);

    t.interrupt();
    assert(t.interruption_requested());

    t.join();
}

//////////////////////////////////////////
void to_interrupt2(int x)
try
{
    using namespace this_thread;
    assert(interruption_enabled());

    for (int i = 0;i < x; ++i)
    {
        disable_interruption di;
        assert(!interruption_enabled());
        cout << i << endl;
        cout << this_thread::interruption_requested() << endl;
        this_thread::interruption_point();

        restore_interruption ri(di);
        assert(interruption_enabled());
        cout << "can interrupted" << endl;
        cout << this_thread::interruption_requested() << endl;
        this_thread::interruption_point();
    }

    assert(interruption_enabled());
}
catch(const thread_interrupted& )
{
    cout << "[thread_interrupted]" << endl;
}

void case6()
{
    thread t(to_interrupt2,10);
    //this_thread::sleep_for(1_s);

    t.interrupt();
    assert(t.interruption_requested());

    t.join();
}
//////////////////////////////////////////
void case7()
{
    thread_group tg;
    tg.create_thread(bind(dummy, 100));
    tg.create_thread(bind(dummy, 200));
    tg.join_all();
}
//////////////////////////////////////////
int g_count;
void init_count(int x)
{
    cout << "should call once." << endl;
    g_count = x;
}

void call_func()
{
    static once_flag once;
    call_once(once, init_count, 10);
}

void case8()
{
    (scoped_thread<>(call_func));
    (scoped_thread<>(call_func));
}

//////////////////////////////////////////
int fab(int n)
{
    if(n == 0 || n == 1)
    {    return 1;  }

    return fab(n-1) + fab(n-2);
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
    case8();
}

