// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
#include <type_traits>
using namespace std;

#include <boost/math/constants/constants.hpp>
using namespace boost::math;

//////////////////////////////////////////

void case1()
{
    cout << setprecision(64);

    auto a = float_constants::pi * 2 * 2;
    cout << "area \t\t= " << a << endl;

    using namespace double_constants;

    auto x = root_two * root_three;
    cout << "root 2 * 3 \t= " << x << endl;

    cout << "root pi \t= " << root_pi << endl;
    cout << "pi pow e \t= " << pi_pow_e << endl;
}

//////////////////////////////////////////
#include <boost/multiprecision/cpp_dec_float.hpp>

void case2()
{
    using namespace constants;

    typedef decltype(pi<float>) pi_t;
    assert(is_function<pi_t>::value);

    assert(pi<float>() == float_constants::pi);
    assert(pi<double>() == double_constants::pi);

    typedef boost::multiprecision::cpp_dec_float_100 float_100;
    cout << setprecision(100)
         << pi<float_100>() << endl;
}

int main()
{
    case1();
    case2();
}


