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
    date d(2014,11,3);
    date_facet* dfacet = new date_facet("%Y年%m月%d日");
    cout.imbue(locale(cout.getloc(), dfacet));
    cout << d << endl;

    time_facet *tfacet = new time_facet("%Y年%m月%d日%H点%M分%S%F秒");
    cout.imbue(locale(cout.getloc(), tfacet));
    cout << ptime(d , hours(21) + minutes(50) + millisec(100)) << endl;

}

//////////////////////////////////////////
days operator"" _D(unsigned long long n)
{
    return days(n);
}

weeks operator"" _W(unsigned long long n)
{
    return weeks(n);
}

date operator"" _YMD(const char*  s, std::size_t )
{
    return from_string(s);
}

void case2()
{
    auto d = 100_D;
    auto w = 1_W;

    assert(d.days() == 100);
    assert(w.days() == (7_D).days());

    auto today = "2014/11/3"_YMD;
    cout  << today << endl;
}

//////////////////////////////////////////
#include <boost/date_time/local_time/local_time.hpp>
using namespace boost::local_time;

void case3()
{
    tz_database tz_db;
    tz_db.load_from_file("./date_time_zonespec.csv");

    time_zone_ptr shz =  tz_db.time_zone_from_region("Asia/Shanghai");

    time_zone_ptr sfz =  tz_db.time_zone_from_region("America/Los_Angeles");

    cout << shz->has_dst() << endl;
    cout << shz->std_zone_name() << endl;

    local_date_time dt_bj(date(2014,3,6),
            hours(16),
            shz,
            false);
    cout << dt_bj << endl;

    time_duration flight_time = hours(12);
    dt_bj += flight_time;
    cout << dt_bj << endl;
    local_date_time dt_sf = dt_bj.local_time_in(sfz);
    cout << dt_sf;
}


//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
}
