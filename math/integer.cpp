// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
#include <type_traits>
using namespace std;

//////////////////////////////////////////

#include <boost/integer_traits.hpp>
using namespace boost;

void case1()
{
    cout << integer_traits<int >::const_max << endl;
    cout << integer_traits<bool>::const_min << endl;
    cout << integer_traits<long>::is_signed << endl;
}

//////////////////////////////////////////

#include <boost/cstdint.hpp>
#include <limits>

void case2()
{
    uint8_t         u8;
    int_fast16_t    i16;
    int_least32_t   i32;
    uintmax_t       um;

    u8  = 255;
    i16 = 32000;
    i32 = i16;
    um  = u8 + i16 + i32;

    cout << "u8 :" << sizeof(u8) 
        << " v = "<< (short)u8 << endl;
    cout << "i16 :" << sizeof(i16) 
        << " v = "<< i16 << endl;
    cout << "i32 :" << sizeof(i32) 
        << " v = "<< i32 << endl;
    cout << "um :" << sizeof(um) 
        << " v = "<< um << endl;

    cout << (short)numeric_limits<int8_t>::max() << endl;
    cout << numeric_limits<uint_least16_t>::max() << endl;
    cout << numeric_limits<int_fast32_t>::max() << endl;
    cout << numeric_limits<intmax_t>::min() << endl;
}

//////////////////////////////////////////

#include <boost/integer.hpp>
#include <boost/type_index.hpp>

void case3()
{
    typedef int_fast_t<char>::fast cfast;
    cout << typeindex::type_id<cfast>().pretty_name() << endl;

    typedef int_fast_t<int>::fast ifast;
    cout << typeindex::type_id<ifast>().pretty_name() << endl;

    typedef int_fast_t<uint16_t>::fast u16fast;
    cout << typeindex::type_id<u16fast>().pretty_name() << endl;
}

//////////////////////////////////////////

#include <boost/format.hpp>

template<typename T>
string type_name()
{
    return typeindex::type_id<T>().pretty_name();
}

void case4()
{
    format fmt("type:%s,size=%dbit\n"); //一个format对象

    typedef uint_t<15>::fast u15;                 //可容纳15位的无符号最快整数
    cout << fmt % type_name<u15>() % (sizeof(u15) * 8) ;

    typedef int_max_value_t<32700>::fast i32700;     //可处理32700的最快整数
    cout << fmt % type_name<i32700>() % (sizeof(i32700) * 8);

    typedef int_min_value_t<-33000>::fast i33000;        //可处理-33000的最快整数
    cout << fmt % type_name<i33000>() % (sizeof(33000) * 8);

    typedef uint_value_t<33000>::fast u33000;            //可处理33000的最快无符号整数
    cout << fmt % type_name<u33000>() % (sizeof(u33000) * 8);
}

int main()
{
    case1();
    case2();
    case3();
    case4();
}

