// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;

//////////////////////////////////////////
void case1()
{
    date_period dp(date(2014,1,1), days(20));

    dp.shift(days(3));
    assert(dp.begin().day() == 4);
    assert(dp.length().days() == 20);

    dp.expand(days(3));
    assert(dp.begin().day() == 1);
    assert(dp.length().days() == 26);

}

//////////////////////////////////////////

void case2()
{
    date_period dp(date(2010,1,1), days(20));

    assert(dp.is_after(date(2009,12,1)));
    assert(dp.is_before(date(2010,2,1)));
    assert(dp.contains(date(2010,1,10)));

    date_period dp2(date(2010,1,5), days(10));
    assert(dp.contains(dp2));

    assert(dp.intersects(dp2));
    assert(dp.intersection(dp2) == dp2);

    date_period dp3(date(2010,1,21), days(5));
    assert(!dp3.intersects(dp2));
    assert(dp3.intersection(dp2).is_null());

    assert(dp.is_adjacent(dp3));
    assert(!dp.intersects(dp3));

}

//////////////////////////////////////////
void case3()
{
    date_period dp1(date(2010,1,1), days(20));
    date_period dp2(date(2010,1,5), days(10));
    date_period dp3(date(2010,2,1), days(5));
    date_period dp4(date(2010,1,15), days(10));

    assert( dp1.contains(dp2) && dp1.merge(dp2) == dp1);
    assert(!dp1.intersects(dp3) && dp1.merge(dp3).is_null());
    assert( dp1.intersects(dp2) && dp1.merge(dp4).end() == dp4.end());
    assert( dp1.span(dp3).end() == dp3.end());
}

//////////////////////////////////////////
void case4()
{
    date d(2006,11,26);
    day_iterator d_iter(d);

    assert(d_iter == d);
    ++d_iter;
    assert(d_iter == date(2006,11,27));

    year_iterator y_iter(*d_iter, 8);
    assert(y_iter == d + days(1));
    ++y_iter;
    assert(y_iter->year() == 2014);

    day_iterator iter(day_clock::local_day());
    ++iter;

    //iter += 5;
    //std::advance(iter, 5);
}

//////////////////////////////////////////
void case5()
{
    typedef gregorian_calendar gre_cal;
    cout << "Y2014 is "
        << (gre_cal::is_leap_year(2014)?"":"not")
        << " a leap year." << endl;
    assert(gre_cal::end_of_month_day(2014, 2) == 28);
}

//////////////////////////////////////////
void case6()
{
    date d(2008,11,20);

    date d_start(d.year(), d.month(), 1);
    date d_end = d.end_of_month();

    for(day_iterator d_iter(d_start);
        d_iter <= d_end; ++d_iter)
    {
            cout << *d_iter << " " <<
                    d_iter->day_of_week()<< endl;
    }

}

//////////////////////////////////////////
void case7()
{
    date d(2008,11,20);

    date d18years = d + years(18);
    cout << d18years << " is "
        << d18years.day_of_week()<< endl;

    int count = 0;
    for (day_iterator d_iter(date(d18years.year(),11,1));
            d_iter <= d18years.end_of_month(); ++d_iter)
    {
        if (d_iter->day_of_week() == Sunday)
        {
            ++count;
        }
    }
    cout << "total " << count << " Sundays." << endl;

    count = 0;
    for (month_iterator m_iter(date(d18years.year(),1,1));
            m_iter < date(d18years.year() + 1 ,1, 1); ++m_iter)
    {
        count += m_iter->end_of_month().day();
    }
    cout << "total " << count << " days of year." << endl;

}

//////////////////////////////////////////
class credit_card
{
public:
    string bank_name;
    int bill_day_no;

    credit_card(const char* bname, int no):
        bank_name(bname), bill_day_no(no){}

    int calc_free_days(date consume_day = day_clock::local_day()) const
    {
        date bill_day(consume_day.year(), consume_day.month(), bill_day_no);
        if (consume_day > bill_day)
        {
            bill_day += months(1);
        }

        return (bill_day - consume_day).days() + 20;
    }

    friend bool operator<(const credit_card& l, const credit_card& r)
    {

        return l.calc_free_days() < r.calc_free_days();
    }
};

void case8()
{
    credit_card a("A bank", 25);
    credit_card b("B bank", 12);

    credit_card tmp = std::max(a, b);
    cout << "You should use " << tmp.bank_name 
        << ", free days = " << tmp.calc_free_days() << endl;
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

