// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;

//////////////////////////////////////////

void case1()
{
    date d1;
    date d2(2010,1,1);
    date d3(2000, Jan , 1);
    date d4(d2);

    assert(d1 == date(not_a_date_time));
    assert(d2 == d4);
    assert(d3 <  d4);
}

//////////////////////////////////////////

void case2()
{
    date d1 = from_string("1999-12-31");
    date d2 ( from_string("2015/1/1") );
    date d3 = from_undelimited_string("20011118") ;

    cout << d1 << d2 << d3 << endl;

    cout << day_clock::local_day()    << endl;
    cout << day_clock::universal_day() << endl;

}

//////////////////////////////////////////
void case3()
{
    date d1(neg_infin);
    date d2(pos_infin);
    date d3(not_a_date_time);
    date d4(max_date_time);
    date d5(min_date_time);

    cout << d1 << d2 << d3 << d4 << d5 << endl;

    try
    {
        //date d1(1399,12,1);
        //date d2(10000,1,1);
        date d3(2010,2,29);
    }
    catch(std::exception& e)
    {
        cout << e.what() << endl;
    }
}

//////////////////////////////////////////
void case4()
{
    date d(2014,4,1);
    assert(d.year()  == 2014);
    assert(d.month() == 4);
    assert(d.day()   == 1);

    date::ymd_type ymd =  d.year_month_day();
    assert(ymd.year    == 2014);
    assert(ymd.month   == 4);
    assert(ymd.day     == 1);

    cout << d.day_of_week() << endl;
    cout << d.day_of_year() << endl;
    assert(d.end_of_month() == date(2014,4,30));

    cout << date(2014,1,10).week_number() << endl;
    cout << date(2014,1,1).week_number()  << endl;
    cout << date(2015,1,1).week_number()  << endl;

    assert(date(pos_infin).is_infinity()  );
    assert(date(pos_infin).is_pos_infinity() );
    assert(date(neg_infin).is_neg_infinity() );
    assert(date(not_a_date_time).is_not_a_date() );
    assert(date(not_a_date_time).is_special() );
    assert(!date(2014,11,1).is_special() );


}

//////////////////////////////////////////
void case5()
{
    date d(2008,11,20);

    cout << to_simple_string(d) << endl;
    cout << to_iso_string(d) << endl;
    cout << to_iso_extended_string(d) << endl;
    cout << d << endl;

    //cout << "input date:";
    //cin >>d;
    //cout << d;

}

//////////////////////////////////////////
void case6()
{
    date d(2014,2,1);
    tm t = to_tm(d);
    assert(t.tm_hour == 0 && t.tm_min == 0);
    assert(t.tm_year == 114 && t.tm_mday == 1);

    date d2 = date_from_tm(t);
    assert(d == d2);

}

//////////////////////////////////////////
void case7()
{
    days dd1(10), dd2(-100), dd3(255);

    assert( dd1 > dd2 && dd1 < dd3);
    assert( dd1 + dd2 == days(-90));
    assert((dd1 + dd3).days() == 265);
    assert( dd3 / 5 == days(51));

    weeks w(3);
    assert(w.days() == 21);

    months m(5);
    years y(2);

    months m2 = y + m;
    assert(m2.number_of_months() == 29);
    assert((y * 2).number_of_years() == 4);

}

//////////////////////////////////////////
void case8()
{
    date d1(2000,1,1),d2(2014,11,18);
    cout << d2 - d1 << endl;
    assert(d1 + (d2 - d1) == d2);

    d1 += days(10);
    assert(d1.day() == 11);
    d1 += months(2);
    assert(d1.month() == 3 && d1.day() == 11);
    d1 -= weeks(1);
    assert(d1.day() == 4);

    d2 -= years(10);
    assert(d2.year() == d1.year() + 4);

    {
        date d1(2014,1,1);

        date d2 = d1 + days(pos_infin);
        assert(d2.is_pos_infinity());

        d2 = d1 + days(not_a_date_time);
        assert(d2.is_not_a_date());
        d2 = date(neg_infin);
        days dd = d1 - d2;
        assert(dd.is_special() && !dd.is_negative());
    }

    {
        date d(2014,3,30);
        d -= months(1);
        d -= months(1);
        d += months(2);
        assert(d.day() == 31);
    }
}

//////////////////////////////////////////
void case9()
{
    date_period dp1(date(2014,1,1), days(20));
    date_period dp2(date(2014,1,1), date(2013,1,1));
    date_period dp3(date(2014,3,1), days(-20));

    date_period dp(date(2014,1,1), days(20));

    assert(!dp.is_null());
    assert(dp.begin().day() == 1);
    assert(dp.last().day() == 20);
    assert(dp.end().day() == 21);
    assert(dp.length().days() == 20);

    {
        date_period dp1(date(2014,1,1), days(20));
        date_period dp2(date(2014,2,19), days(10));

        cout << dp1;                        //[2010-Jan-01/2010-Jan-20]
        assert(dp1 < dp2);
    }
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
}


