// Copyright (c) 2015
// Author: Chrono Law
#include <type_traits>
#include <std.hpp>
using namespace std;

#define BOOST_DISABLE_ASSERTS
#include <boost/optional.hpp>
using namespace boost;

//////////////////////////////////////////
void case1()
{
    cout << typeid(none).name() << endl;
    cout << std::is_member_object_pointer<none_t>::value << endl;
}

//////////////////////////////////////////
void case2()
{
    optional<int> op0;
    optional<int> op1(none);

    assert(!op0);
    assert(op0 == op1);
    assert(op1.value_or(253) == 253);

    cout << op1.value_or_eval(
            [](){return 874;}) << endl;

    optional<string> ops("test");
    cout << *ops << endl;

    ops.emplace("monado", 3);
    assert(*ops == "mon");

    vector<int> v(10);
    optional<vector<int>& > opv(v);
    assert(opv);

    opv->push_back(5);
    assert(opv->size() == 11);

    opv = none;
    assert(!opv);
}

//////////////////////////////////////////
optional<double> calc(int x)
{
    return optional<double>( x != 0, 1.0 / x);
}

optional<double> sqrt_op(double x)
{
    return optional<double>(x > 0, sqrt(x));
}

void case3()
{
    optional<double> d = calc(10);

    if (d)
    {
        cout << *d << endl;
        cout << d.value() << endl;
    }

    d = sqrt_op(-10);
    if (!d)
    {   cout << "no result"<< endl; }
}

//////////////////////////////////////////
void case4()
{
    auto x = make_optional(5);
    assert(*x == 5);

    auto y = make_optional<double>((*x > 10), 1.0);
    assert(!y);
}


//////////////////////////////////////////
int main()
{
    case1();
    case2();
    case3();
    case4();
}
