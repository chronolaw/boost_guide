// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
//using namespace std;

#include <boost/ref.hpp>
using namespace boost;

struct square
{
    typedef void result_type;
    result_type operator()(int &x)
    {   x = x * x;  }
};

//////////////////////////////////////////

void case1()
{
    std::vector<int> v = {1,2,3,4,5};
    for_each(v.begin(), v.end(), square());
}

//////////////////////////////////////////

void case2()
{
    int x = 10;
    reference_wrapper<int> rw(x);
    assert(x == rw);
    (int &)rw = 100;
    assert(x == 100);

    reference_wrapper<int> rw2(rw);
    assert(rw2.get() == 100);

    std::string str;
    reference_wrapper<std::string> rws(str);
    *rws.get_pointer() = "test reference_wrapper";
    std::cout << rws.get().size() << std::endl;

}

//////////////////////////////////////////

void case3()
{
    double x = 2.71828;
    auto rw = cref(x);
    std::cout << typeid(rw).name() << std::endl;

    std::string str;
    auto rws = boost::ref(str);
    std::cout << typeid(rws).name() << std::endl;

    boost::cref(str);   //adl

    std::cout << std::sqrt(ref(x)) << std::endl;      //计算平方根
}

//////////////////////////////////////////

void case4()
{
    std::vector<int> v(10, 2) ;
    auto rw = boost::cref(v);

    assert( is_reference_wrapper<decltype(rw)>::value);
    assert(!is_reference_wrapper<decltype(v)>::value);

    std::string str;
    auto rws = boost::ref(str);
    std::cout << typeid(unwrap_reference<decltype(rws)>::type).name() << std::endl;
    std::cout << typeid(unwrap_reference<decltype(str)>::type).name() << std::endl;

}

//////////////////////////////////////////

void case5()
{
    std::set<int> s ;
    auto rw = boost::ref(s);
    unwrap_ref(rw).insert(12);

    std::string str("test");
    auto rws = boost::cref(str);
    std::cout << unwrap_ref(rws) << std::endl;
    std::cout << unwrap_ref(str) << std::endl;

}

//////////////////////////////////////////

class big_class
{
private:
    int x;
public:
    big_class():x(0){}
    void print()
    {   std::cout << "big_class " << ++x << std::endl;    }
};
template<typename T>
void print(T a)
{
    for (int i = 0;i < 2; ++i)
        unwrap_ref(a).print();
}
void case6()
{
    big_class c;
    auto rw = ref(c);
    c.print();

    print(c);
    print(rw);
    print(c);
    c.print();
}

void case7()
{
    using namespace std;

    typedef double (*pfunc)(double);
    pfunc pf = sqrt;
    cout << std::ref(pf)(5.0) << endl;

    square sq;
    int x =5;
    std::ref(sq)(x);
    cout << x << endl;

    vector<int> v = {1,2,3,4,5};
    for_each(v.begin(), v.end(), std::ref(sq));
}


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
