// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/lexical_cast.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    int  x      = lexical_cast<int>("100");
    long y      = lexical_cast<long>("2000");
    float pai   = lexical_cast<float>("3.14159e5");
    double e    = lexical_cast<double>("2.71828");
    double r    = lexical_cast<double>("1.414,xyz", 5);

    cout << x << y << pai << e << r << endl;

    string str = lexical_cast<string>(456);
    cout << str << endl;

    cout << lexical_cast<string>(0.618) << endl;
    cout << lexical_cast<string>(0x10) << endl;

    cout << lexical_cast<bool>("1") << endl;

    //lexical_cast<int>("0x100");
    //lexical_cast<int>("123L");
}

//////////////////////////////////////////

template<typename T>
bool num_valid(const char *str)
{
    T tmp;
    return conversion::try_lexical_convert(str, tmp);
}
//try
//{
//    lexical_cast<T>(str);
//    return true;
//}
//catch(bad_lexical_cast&)
//{
//    return false;
//};

void case2()
try
{
    assert( num_valid<double>("3.14"));
    assert(!num_valid<int>("3.14"));
    assert( num_valid<int>("65535"));

    int x;
    assert(!conversion::try_lexical_convert("0x100", x));

    cout << lexical_cast<int>("0x100");
    cout << lexical_cast<double>("HelloWorld");
    cout << lexical_cast<long>("1000L");
    cout << lexical_cast<bool>("false") << endl;
}
catch (bad_lexical_cast& e)
{
        cout << "error:" << e.what() << endl;
}

//////////////////////////////////////////
template<typename T>
struct outable
{
    friend std::ostream& operator<<(std::ostream& os, const T& x)
    {
        os << typeid(T).name();
        return os;
    }
};

class demo_class : public outable<demo_class>
{
//    friend std::ostream& operator<<(std::ostream& os, const demo_class& x)
//    {
//        os << "demo_class's Name";
//        return os;
//    }
};
void case3()
{
    cout << lexical_cast<string>(demo_class()) << endl;
}

//////////////////////////////////////////

void case4()
try
{
    assert(stoi(" 42 ") == 42);
    assert(stol("100L") == 100L);
    assert(stol("1000 9") == 1000L);
    assert(stod("3.14ispai") == 3.14);

    assert(to_string(776ul) == "776");

    //cout << stoul("100L");
    //cout << stoul("x100");
    cout << stoi("9999999999");
}
catch(std::exception& e)
{
    cout << "error:" << e.what() << endl;
}

//////////////////////////////////////////
template<typename T>
T std_lexical_cast(const std::string& s);

template<>
int std_lexical_cast<int>(const std::string& s)
{
    return stoi(s);
}

template<>
long std_lexical_cast<long>(const std::string& s)
{
    return stol(s);
}

void case5()
{
    assert(std_lexical_cast<int>(" 10 ") == 10);
    assert(std_lexical_cast<long>("100L") == 100L);
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

