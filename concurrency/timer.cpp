// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#define BOOST_ASIO_DISABLE_STD_CHRONO
//#define BOOST_ASIO_ENABLE_HANDLER_TRACKING
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
//#include <boost/asio/use_future.hpp>
using namespace boost::asio;
using namespace boost::system;

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

//////////////////////////////////////////
void case1()
{
    io_service io;

    steady_timer t(io, 500_ms);
    cout << t.expires_at() << endl;
    cout << t.expires_from_now() << endl;

    t.wait();
    cout << "hello asio1" << endl;
}

//////////////////////////////////////////

void case2()
{
    io_service io;

    steady_timer t(io, 500_ms);

    t.async_wait(
        [](const error_code& ec) {
            cout << "hello asio2" << endl;
        });

    io.run();
}
//////////////////////////////////////////
class timer_with_func
{
    typedef timer_with_func this_type;
private:
    int m_count = 0;
    int m_count_max = 0;
    function<void()> m_f;
    steady_timer m_t;
public:
    template<typename F>
    timer_with_func(io_service& io, int x, F func):
        m_count_max(x),
        m_f(func),
        m_t(io, 200_ms)
    {
        init();
    }

private:
    typedef void(handler_type)(const error_code&);
    function<handler_type> m_handler =
        [&](const error_code&)
        {
            if (m_count++ >= m_count_max)
            {   return;  }
            m_f();

            m_t.expires_from_now(200_ms);
            m_t.async_wait(m_handler);
        };

    void init()
    {
        m_t.async_wait(m_handler);

        //m_t.async_wait(bind(
        //        &this_type::handler, this,
        //        boost::asio::placeholders::error));
        //        //_1));
    }

    void handler(const error_code&)
    {
        if (m_count++ >= m_count_max)
        {   return;  }

        m_f();

        m_t.expires_from_now(200_ms);

        m_t.async_wait(bind(
                &this_type::handler, this,
                boost::asio::placeholders::error));
    }
};

void case3()
{
    io_service io;

    timer_with_func t1(io, 5,
        []{cout << "hello timer1"<<endl;});

    //timer_with_func t2(io, 5,
    //    []{cout << "hello timer2"<<endl;});

    io.run();
}

//////////////////////////////////////////

int main()
{
    //case1();
    //case2();
    case3();
}

