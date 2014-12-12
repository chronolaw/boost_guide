// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/exception/all.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/assign.hpp>
#include <boost/any.hpp>
using namespace boost;

//////////////////////////////////////////
void case1()
{
    any a(10);

    int n = any_cast<int>(a);
    assert(n == 10);

    any_cast<int&>(a) = 20;
    assert(any_cast<int>(a) == 20);;

    try
    {
        any a;
        any_cast<int>(a);
    }
    catch(boost::exception&)
    {   
        cout << current_exception_diagnostic_information();
    }

    any a1, a2(2.0);
    assert(any_cast<int*>(&a1) == nullptr);
    assert(any_cast<string*>(&a2) == nullptr);

}

//////////////////////////////////////////
void case2()
{
    any a(100);
    a = string("char*");
    a = vector<vector<int> >();

    a = "c str";
    cout << a.type().name() << endl;
    cout << any_cast<const char*>(&a) << endl;
    cout << any_cast<const char*>(a) << endl;

    string *ps = new string("abc");     //不好的使用方式
    a = ps;
    if (!a.empty() && any_cast<string*>(a))
    {       cout << *any_cast<string*>(a)<< endl;   }

}

//////////////////////////////////////////
template<typename T>
bool can_cast(any &a)
{   return typeid(T) == a.type();}

template<typename T>
T& get(any &a)
{
    assert(can_cast<T>(a));
    return *any_cast<T>(&a);
}

template<typename T>
T* get_pointer(any &a)
{
    assert(can_cast<T>(a));
    return any_cast<T>(&a);
}

template<typename T>
any make_ptr_any(T *p = 0)
{   return any(boost::shared_ptr<T>(p));}

template<typename T>
boost::shared_ptr<T>& get_shared(any &a)
{
    assert(can_cast<boost::shared_ptr<T> >(a));
    return *any_cast<boost::shared_ptr<T> >(&a);
}

void case3()
{
    any a;
    int x = 1;
    a = x;
    assert(can_cast<int>(a));
    get<int>(a) = 10;
    *get_pointer<int>(a) = 20;

    a = make_ptr_any<string>(new string("long"));
    cout << *get_shared<string>(a) << endl;
    a = make_ptr_any<vector<int> >(new vector<int>);

}

//////////////////////////////////////////
template<typename T > struct any_print
{
    void operator()(any &a)
    try
    {
        cout << *any_cast<T>(&a) << endl;   
    }
    catch(bad_any_cast &)
    {
        cout << "print error" << endl;
    }

};

template<typename T >
struct any_print<boost::shared_ptr<T> >
{
    void operator()(any &a)
    try
    {
        cout << **any_cast<boost::shared_ptr<T> >(&a) << endl; 
    }
    catch(bad_any_cast &)
    {
        cout << "print error" << endl;
    }
};

void case4()
{
    any a;

    a = 10;
    any_print<int>()(a);

    auto ps = boost::make_shared<string>("metroid");
    a = ps;
    any_print< boost::shared_ptr<string> >()(a);

}

//////////////////////////////////////////
void case5()
{
    vector<any> v;
    v.push_back(10);                                    //int
    v.push_back(1.414);                                 //double
    v.push_back(boost::shared_ptr<int>(new int(100) ));    //shared_ptr

    using namespace boost::assign;
    vector<any> v2 = list_of<any>(10)(0.618)(string("char"));
    cout << v2.size();

}

//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
    case4();
    case5();
}
