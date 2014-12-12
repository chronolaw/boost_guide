// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/assign.hpp>
#include <boost/variant.hpp>
using namespace boost;

//////////////////////////////////////////
void case1()
{
    variant<int, float, string> v;
    v = "123";

    cout << v << endl;
}

//////////////////////////////////////////
void case2()
{
    typedef variant<int, double, string> var_t;

    var_t v(1);                                 //v->int
    v = 2.13;                                       //v->double
    assert(v.type() == typeid(double));

    var_t v2("string type");                        //v2->string
    cout << get<string>(v2);

    v2 = v;                                         //v2->double

    cout << get<int>(var_t(108));

}

//////////////////////////////////////////
void case3()
{
    typedef variant<int, double, string> var_t;
    var_t v;
    assert(v.type() == typeid(int));
    assert(v.which() == 0);

    v = "variant demo";
    cout << *get<string>(&v) << endl;

    try
    {
        cout << get<double>(v) << endl;
    }
    catch (bad_get &)
    {
        cout << "bad_get" << endl;
    }
}

//////////////////////////////////////////

struct var_print : public static_visitor<>
{
    template<typename T>
    void operator()(T &i) const
    {
        i *= 2;
        cout << i << endl;
    }

    void operator()(vector<int> &v) const
    {
        v.reserve(v.size()*2);
        copy(v.begin(),v.end(),back_inserter(v)) ;
        for (auto& x : v)
        {
            cout << x << ",";                       //输出以验证
        }
        cout << endl;
    }

};

void case4()
{
    typedef variant<int, double, vector<int> > var_t;

    var_t v(1);
    var_print vp;

    apply_visitor(vp, v);
    v = 3.414;
    apply_visitor(vp, v);

    //using namespace boost::assign;
    //v = vector<int>({1,2});
    vector<int> tmp = {1,2};
    v = tmp;
    apply_visitor(vp, v);

    auto vp2 = apply_visitor(vp);
    vp2(v);

}

//////////////////////////////////////////
template<BOOST_VARIANT_ENUM_PARAMS(typename T)>
void op_var(variant<BOOST_VARIANT_ENUM_PARAMS(T)>& v)
{   cout << v << endl;}

#include <boost/mpl/vector.hpp>
void case5()
{
    typedef boost::mpl::vector<
        int, double, std::vector<string> > var_types;

    make_variant_over<var_types>::type v;
    v = 2.13;

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
