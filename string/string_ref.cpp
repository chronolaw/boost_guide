// Copyright (c) 2015
// Author: Chrono Law
#include <cstring>
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>
#include <boost/utility/string_ref.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    const char* ch = "Days of Future Past";
    string str(ch);

    string_ref s1(ch);
    string_ref s2(str);
    assert(s1 == s2 && s1 == ch && s2 == str);

    string_ref s3(ch, 4);
    assert(s3 == str.substr(0, 4));

    string_ref s4, s5;
    s4  = ch;
    s5 = str;
    assert(s4 == s5);

    //boost::ignore_unused(s4, s5);

}
//////////////////////////////////////////

void case2()
{
    const char* ch = "Apple iPhone iPad";

    string_ref str(ch);

    assert(!str.empty());
    assert(str.size() == strlen(ch));

    for(auto& x : str)
    {
        cout << x ;
    }
    cout << endl;

    assert(str.front() == 'A');
    assert(str[1] == 'p');
    assert(str.find('i') == 6);

    auto substr = str.substr(6, 6);
    assert(substr == "iPhone");

    string s = str.to_string();
    assert(str == s);
    assert(str == ch);

    str.clear();
    assert(str.empty());
}

//////////////////////////////////////////
void case3()
{
    //const char* ch = "Apple iPhone iPad";

    string_ref str("Apple iPhone iPad");

    str.remove_prefix(6);
    assert(str.starts_with("iP"));

    str.remove_suffix(5);
    assert(str.ends_with("one"));
}

//////////////////////////////////////////

void case4()
{
    auto trunk = []
    (string_ref str)->string_ref
    {
        return str.substr(0, 5);
    };

    cout << trunk("abcdefg") << endl;
}

//////////////////////////////////////////


int main()
{
    case1();
    case2();
    case3();
    case4();
}

