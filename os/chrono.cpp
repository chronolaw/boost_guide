// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#define BOOST_ERROR_CODE_HEADER_ONLY
#define BOOST_CHRONO_HEADER_ONLY
#define BOOST_CHRONO_EXTENSIONS
#include <boost/chrono.hpp>
using namespace boost;
using namespace boost::chrono;

//////////////////////////////////////////
typedef duration<long,   ratio<30>> half_min;
typedef duration<int,    ratio<60*15>> quater;
typedef duration<double, ratio<3600*24>> day;

//typedef duration<int,60*60> my_hour;
//typedef duration<int,ratio<-10, 1000>> my_ms;
void case1()
{
    seconds s(10);
    minutes m(5);
    hours   h(1);
    milliseconds ms(100);

    assert(s.count() == 10);
    assert(ms.count() == 100);

    s *= 3;
    s += seconds(30);
    s = s - seconds(20);
    assert(s < seconds(50));
    cout << s << endl;

}

//////////////////////////////////////////
void case2()
{
    seconds s(10);
    minutes m(5);

    s += m;
    cout << s << endl;

    //m+= s;

    {
        seconds s(10);
        typedef duration<double, ratio<60>> my_min;
        my_min m(5);
        m += s;
        cout << m << endl;
    }

    {
        seconds s(40);
        auto m = duration_cast<minutes>(s);
        cout << m << endl;

        seconds s2(301);
        cout << duration_cast<minutes>(s2) << endl;
    }

    {
        seconds s(3600 + 50);
        cout << floor<minutes>(s) << endl;
        cout << ceil<minutes>(s) << endl;
        cout << round<minutes>(s) << endl;
        cout << round<hours>(s) << endl;
    }
}

//////////////////////////////////////////
template<typename T>
using clock_desc = clock_string<T, char>;

void case3()
{
    cout << clock_desc<system_clock>::name() << endl;
    cout << clock_desc<system_clock>::since() << endl;

    cout << clock_desc<steady_clock>::name() << endl;
    cout << clock_desc<steady_clock>::since() << endl;

    cout << clock_desc<process_real_cpu_clock>::name() << endl;
    cout << clock_desc<process_real_cpu_clock>::since() << endl;
}

//////////////////////////////////////////
void case4()
{
    auto tp1 = system_clock::now();
    cout << tp1 << endl;

    auto d = tp1.time_since_epoch();
    cout << duration_cast<hours>(d) << endl;
    cout << duration_cast<day>(d) << endl;

    auto tp2 = tp1 +minutes(1);
    cout << tp2 << endl;

    {
        auto tp = steady_clock::now();
        cout << tp << endl;

        auto d = tp.time_since_epoch();
        cout << round<minutes>(d) << endl;
    }
}

//////////////////////////////////////////
hours operator"" _h(unsigned long long n)
{
    return hours(n);
}

seconds operator"" _s(unsigned long long n)
{
    return seconds(n);
}

milliseconds operator"" _ms(unsigned long long n)
{
    return milliseconds(n);
}
void case5()
{
    auto h = 5_h;
    auto s = 45_s;
    auto ms = 200_ms;

    cout << h << s << ms << endl;
}
//////////////////////////////////////////
void case6()
{
    auto tp = system_clock::now();
    auto t = system_clock::to_time_t(tp);

    cout << std::ctime(&t) << endl;
}

//////////////////////////////////////////
class steady_timer final
{
private:
    typedef boost::chrono::steady_clock clock_type;

    //typedef clock_type::duration duration_type;
    typedef clock_type::time_point time_point_type;
    typedef boost::chrono::microseconds duration_type;

    time_point_type m_start = clock_type::now();
public:
    steady_timer() = default;
    ~steady_timer() = default;
public:
    void restart()
    {
        m_start = clock_type::now();
    }

    duration_type elapsed() const
    {
        return round<duration_type>(
                clock_type::now() - m_start);
    }
};

//////////////////////////////////////////

int main()
{
    steady_timer t;

    case1();
    case2();
    case3();
    case4();
    case5();
    case6();

    cout << t.elapsed() << endl;
}
