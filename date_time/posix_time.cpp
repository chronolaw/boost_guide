// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

//#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;

//////////////////////////////////////////

void case1()
{
    {
        time_duration td = duration_from_string("1:10:30:001");
        cout << td << endl;

        time_duration td1(1,10,30,1000);
        time_duration td2(1,60,60,1000*1000* 6 + 1000);
    }

    hours h(1);
    minutes m(10);
    seconds s(30);
    millisec ms(1);

    time_duration td = h + m + s + ms;
    time_duration td2 = hours(2) + seconds(10);

    cout << td << td2 << endl;
}

//////////////////////////////////////////
void case2()
{
    time_duration td(1,10,30,1000);
    assert(td.hours() == 1 && td.minutes() == 10 && td.seconds() == 30);
    assert(td.total_seconds() == 1*3600+ 10*60 + 30);
    assert(td.total_milliseconds() == td.total_seconds()*1000 + 1);
    assert(td.fractional_seconds() == 1000);

    hours h(-10);
    assert(h.is_negative());

    time_duration h2 = h.invert_sign();
    assert(!h2.is_negative() && h2.hours() == 10);

    time_duration td1(not_a_date_time);
    assert(td1.is_special() && td1.is_not_a_date_time());

    time_duration td2(neg_infin);
    assert(td2.is_negative() && td2.is_neg_infinity());

}

//////////////////////////////////////////
void case3()
{
    time_duration td1 = hours(1);
    time_duration td2 = hours(2) + minutes(30);
    assert(td1 < td2);
    assert((td1+td2).hours() == 3);
    assert((td1-td2).is_negative());
    assert(td1 * 5 == td2 * 2);
    assert((td1/2).minutes() == td2.minutes());

    time_duration td(1,10,30,1000);
    cout << to_simple_string(td) << endl;
    cout << to_iso_string(td) << endl;

}

//////////////////////////////////////////
void case4()
{
#ifdef BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
    time_duration td(1,10,30,1000);
    cout << td;
    assert(td.total_milliseconds() ==
            td.total_seconds()*1000);

    assert(td.fractional_seconds() ==1000);
    assert(time_duration::unit()*1000*1000*1000 == seconds(1));

    assert(td.resolution() == boost::date_time::nano);
    assert(td.num_fractional_digits() == 9);


#endif
}

//////////////////////////////////////////
void case5()
{
    ptime p(date(2014,6,8), hours(1));
    ptime p1 = time_from_string("2014-6-8 01:00:00");
    ptime p2 = from_iso_string("20140608T010000");

    cout << p1 << endl << p2;
    {
        ptime p1 = second_clock::local_time();
        ptime p2 = microsec_clock::universal_time();
        cout << p1 << endl << p2;

    }
}

//////////////////////////////////////////
void case6()
{
    ptime p(date(2010,3,20), hours(12)+minutes(30));

    date d = p.date();
    time_duration td = p.time_of_day();
    assert(d.month() == 3 && d.day() == 20);
    assert(td.total_seconds() == 12*3600 + 30*60);

    ptime p1(date(2010,3,20), hours(12)+minutes(30));
    ptime p2 = p1 + hours(3);

    assert(p1 < p2);
    assert(p2 - p1 == hours(3));
    p2 += months(1);
    assert(p2.date().month() == 4);

    cout << endl;
    {
        ptime p(date(2014,2,14), hours(20));
        cout << to_simple_string(p) << endl;
        cout << to_iso_string(p) << endl;
        cout << to_iso_extended_string(p) << endl;
    }
}

//////////////////////////////////////////
void case7()
{
    ptime p(date(2010,2,14), hours(20));
    tm t = to_tm(p);
    assert(t.tm_year == 110 && t.tm_hour == 20);

    ptime p2 = from_time_t(std::time(0));
    assert(p2.date() == day_clock::local_day());
}

//////////////////////////////////////////
void case8()
{
    ptime p(date(2014,1,1),hours(12)) ;
    time_period tp1(p, hours(8));
    time_period tp2(p + hours(8), hours(1));
    assert(tp1.end() == tp2.begin() && tp1.is_adjacent(tp2));
    assert(!tp1.intersects(tp2));

    tp1.shift(hours(1));
    assert(tp1.is_after(p));
    assert(tp1.intersects(tp2));

    tp2.expand(hours(10));
    assert(tp2.contains(p) && tp2.contains(tp1));
}

//////////////////////////////////////////
void case9()
{
    ptime p(date(2014,11,3),hours(10)) ;
    for (time_iterator t_iter(p, minutes(10));
            t_iter < p + hours(1); ++ t_iter)
    {
            cout << *t_iter << endl;
    }

}

//////////////////////////////////////////
template<typename Clock = microsec_clock>
class basic_ptimer
{
    public:
        basic_ptimer()
        {   restart();}
        void restart()
        {   _start_time = Clock::local_time();  }
        void elapsed() const
        {   cout << Clock::local_time() - _start_time;  }
        ~basic_ptimer()
        {   elapsed();  }
    private:
        ptime _start_time;
};
typedef basic_ptimer<microsec_clock> ptimer;
typedef basic_ptimer<second_clock>   sptimer;

class work_time
{
public:
    typedef map<time_period, string> map_t;
private:
    map_t map_ts;
    void init()
    {
        ptime p(day_clock::local_day());

        map_ts[time_period(p, hours(9))] = "It's too early, just relax.\n";
        p += hours(9);
        map_ts[time_period(p, hours(3)+ minutes(30))] = "It's AM, please work hard.\n";
        p += hours(3)+ minutes(30);
        map_ts[time_period(p, hours(1))] = "It's lunch time, are you hungry?\n";
        p += hours(1);
        map_ts[time_period(p, hours(4)+minutes(30))] = "It's PM, ready to go home.\n";
        p += hours(4)+ minutes(30);
        map_ts[time_period(p, hours(6))] = "Are you still working? you do need a rest.\n";
    }
public:
    work_time()
    {   init(); }

    void greeting(const ptime& t)
    {
        for (auto& x : map_ts)
        {
            if (x.first.contains(t))
            {
                cout << x.second << endl;
                break;
            }
        }
    }
};

void case10()
{
    ptimer t;

    work_time wt;
    wt.greeting(second_clock::local_time());
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
    case9();
    case10();
}
