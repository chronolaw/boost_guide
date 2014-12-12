// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
//using namespace std;

#include <boost/core/ignore_unused.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple_io.hpp>
using namespace boost;

//////////////////////////////////////////
typedef tuple<int, std::string>    my_tuple1;
typedef tuple<int, my_tuple1> my_tuple2;

typedef tuple<void>             no_instance_t1;
typedef tuple<double(int)>  no_instance_t2;

void case1()
{
    typedef tuple<int, std::string, double> my_tuple;
    my_tuple t1;
    my_tuple t2(1, "123");
    my_tuple t3(t1);
    t2 = t3;

    int x = 10;
    tuple<int&> t4(x);

    {
        tuple<void*> t1;
        tuple<double(*)(int)> t2;
    }

    {
        boost::make_tuple(2, 3.0);
        boost::make_tuple(std::string(), std::vector<int>());

        int i;
        std::string s;
        tuple<int, std::string&>     t1       = boost::make_tuple(i, boost::ref(s));
        tuple<const int&, std::string&>  t2   = boost::make_tuple(boost::cref(i),boost::ref(s));

        boost::ignore_unused(t1, t2);
    }

}

//////////////////////////////////////////
void case2()
{
    auto t = make_tuple(1, "char[]", 100.0);

    assert(t.get<0>() == 1);
    assert(t.get<2>() == 100.0);

    std::cout << t.get<1>();
    std::cout << ++t.get<0>();

    std::cout << std::endl;

    get<0>(t);
    get<1>(t);

}

//////////////////////////////////////////
void case3()
{
    typedef boost::tuple<int ,double ,std::string> my_tuple;    //3-tuple

    my_tuple t1 = boost::make_tuple(1, 100.0, std::string("abc"));
    my_tuple t2 = boost::make_tuple(1, 200.0, std::string("def"));
    assert(t1 < t2);

    my_tuple t3(t2);
    assert(t2 == t3);
}

//////////////////////////////////////////
void case4()
{
    typedef boost::tuple<int ,double ,std::string> my_tuple;

    my_tuple t1(1, 2.0, "string");
    std::cout << t1 << std::endl;

    //std::cout << "please input tuple:";
    //std::cin >> t1;

    //std::cout << t1 << std::endl;
    std::cout << tuples::set_open('[') << tuples::set_close(']');
    std::cout << tuples::set_delimiter(',');
    std::cout << t1 << std::endl;

}

//////////////////////////////////////////
typedef tuple<int ,double ,std::string> my_tuple;

my_tuple func()
{   return boost::make_tuple(1, 2.0, "string");}

void case5()
{
    int i;double d;std::string s;
    tie(i, d, s) = func();
    std::cout << i;

    tie(tuples::ignore, d, tuples::ignore) = func();
}

//////////////////////////////////////////
#include <boost/assign.hpp>
void case6()
{
    typedef boost::tuple<int ,double ,std::string> my_tuple;
    using namespace boost::assign;

    std::vector<my_tuple> v = tuple_list_of(1, 1.0, "123")(2, 2.0, "456");
    assert(v.size() == 2);

    v += boost::make_tuple(3, 3.0, "789"),boost::make_tuple(4, 4.0, "abc");
    assert(v.size() == 4);

}

//////////////////////////////////////////
template <typename Tuple>
void print_tuple(const Tuple& t)
{
    std::cout << t.get_head() << ',';
    print_tuple(t.get_tail());
}
template<>
void print_tuple(const tuples::null_type&) {}

void case7()
{
    typedef boost::tuple<int , double ,std::string> t_type;
    t_type  t(1, 2.1, "string tuple");
    print_tuple(t);

}

//////////////////////////////////////////
template<typename Visitor, typename Tuple>
typename Visitor::result_type
visit_tuple(Visitor v, const Tuple &t)
{
    v(t.get_head());
    return visit_tuple(v, t.get_tail());
};

struct print_visitor
{
    typedef void result_type;
    template<typename T>
        result_type operator()(const T &t)
        {
            std::cout << t << ",";
        }
};
template<>
void visit_tuple//< print_visitor,  tuples::null_type>
    (print_visitor , const tuples::null_type &)
    {}

template<typename T>
struct max_visitor
{
    T *tmp;                                             //最大值
    max_visitor(T *t):tmp(t){}
    typedef void result_type;
    result_type operator()(const T &t)
    {   *tmp = *tmp < t? t : *tmp;  }
};

template<>
void visit_tuple//< max_visitor<double>,  tuples::null_type>
(max_visitor<double> , const tuples::null_type &)
{}

void case8()
{
    boost::tuple<int , double ,std::string>  t(1, 2.1, "string visitor");
    visit_tuple(print_visitor(), t);

    {
        boost::tuple<int, long, float, double> t(100, 5, 3.14, 314.15);
        double *max_value = new double(t.get_head());
        max_visitor<double> mv(max_value);
        visit_tuple(mv, t);
        std::cout << *max_value  << std::endl;
    }

    typedef boost::tuple<int , std::string> my_tuple1;
    typedef boost::tuple<int, my_tuple1> my_tuple2;

    assert(typeid(int) == typeid(tuples::element<0, my_tuple1>::type));
    assert(typeid(std::string) == typeid(tuples::element<1, my_tuple1>::type));
    std::cout << tuples::length<my_tuple2>::value << std::endl;

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
