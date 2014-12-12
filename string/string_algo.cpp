// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/utility/string_ref.hpp>
#include <boost/algorithm/string.hpp>
using namespace boost;

//////////////////////////////////////////

void case1()
{
    string str("readme.txt");

    if (ends_with(str, "txt"))
    {
        cout << to_upper_copy(str) + " UPPER" << endl;
        assert(ends_with(str, "txt"));
    }

    replace_first(str, "readme", "followme");
    cout << str << endl;

    vector<char> v(str.begin(), str.end());
    vector<char> v2 = to_upper_copy(
            erase_first_copy(v, "txt"));
    for (auto ch : v2)
    {   cout << ch; }
}

//////////////////////////////////////////
void case2()
{
    string str("I Don't Know.\n");
    cout << to_upper_copy(str);
    cout << str;
    to_lower(str);
    cout << str;
}

//////////////////////////////////////////
void case3()
{
    string str("Power Bomb");

    assert(iends_with(str, "bomb"));
    assert(!ends_with(str, "bomb"));

    assert(starts_with(str, "Pow"));

    assert(contains(str, "er"));

    string str2 = to_lower_copy(str);
    assert(iequals(str, str2));

    string str3("power suit");
    assert(ilexicographical_compare(str, str3));

    assert(all(str2.substr(0, 5), is_lower()));
}

//////////////////////////////////////////
void case4()
{
    string str1("Samus"), str2("samus");

    assert(!is_equal()(str1, str2));
    assert( is_less()(str1, str2));

    //cout << (to_upper_copy(str1) == to_upper_copy(str2)) << endl;
    //cout << is_iequal()(str1, str2) << endl;
    assert(!is_equal()(str1, string_ref(str2)));
}

//////////////////////////////////////////
#include <boost/format.hpp>

struct is_zero_or_one
{
    bool operator()(char x)
    {   return x == '0' || x == '1';}
};

auto is01 = [](char x)
    {   return x == '0' || x == '1';};

void case5()
{
    format fmt("|%s|\n");

    string str = "  samus aran   ";
    cout << fmt % trim_copy(str);
    cout << fmt % trim_left_copy(str);

    trim_right(str);
    cout << fmt % str;

    string str2 = "2015 Happy new Year!!!";
    cout << fmt % trim_left_copy_if(str2, is_digit());
    cout << fmt % trim_right_copy_if(str2, is_punct());
    cout << fmt % trim_copy_if(str2,
            is_punct() || is_digit() || is_space());
}

//////////////////////////////////////////
void case6()
{
    format fmt("|%s|. pos = %d\n");

    string str = "Long long ago, there was a king.";

    iterator_range<string::iterator> rge;

    rge = find_first(str, "long");
    cout << fmt % rge % (rge.begin() - str.begin());

    rge = ifind_first(str, "long");
    cout << fmt % rge % (rge.begin() - str.begin());

    rge = find_nth(str, "ng", 2);
    cout << fmt % rge % (rge.begin() - str.begin());

    rge = find_head(str, 4);
    cout << fmt % rge % (rge.begin() - str.begin());

    rge = find_tail(str, 5);
    cout << fmt % rge % (rge.begin() - str.begin());

    rge = find_first(str, "samus");
    assert(rge.empty() && !rge);
}


//////////////////////////////////////////
void case7()
{
    string str = "Samus beat the monster.\n";

    cout << replace_first_copy(str, "Samus", "samus");

    replace_last(str, "beat", "kill");
    cout << str;

    replace_tail(str, 9, "ridley.\n");
    cout << str;

    cout << ierase_all_copy(str, "samus");
    cout << replace_nth_copy(str, "l", 1, "L");
    cout << erase_tail_copy(str, 8);
}

//////////////////////////////////////////
void case8()
{
    string str = "Samus,Link.Zelda::Mario-Luigi+zelda";

    deque<string> d;
    ifind_all(d, str, "zELDA");
    assert(d.size() == 2);
    for (auto x : d)
    {   cout << "["<< x << "] ";    }
    cout << endl;

    list<iterator_range<string::iterator> > l;
    split(l, str, is_any_of(",.:-+"));
    for (auto x : l)
    {   cout << "["<< x << "]"; }
    cout << endl;

    l.clear();
    split(l, str, is_any_of(".:-"), token_compress_on);
    for (auto x : l)
    {   cout << "["<< x << "]"; }
    cout << endl;
}


//////////////////////////////////////////
#include <boost/assign.hpp>
void case9()
{
    using namespace boost::assign;
    vector<string> v = list_of("Samus")("Link")("Zelda")("Mario");
    cout << join(v, "+") << endl;

    //cout << join_if(v, "**", is_contains_a());
    cout << join_if(v, "**",
                    [](string_ref s)
                    { return contains(s, "a"); }
                    );
    cout << endl;
}

//////////////////////////////////////////
void case10()
{
    string str("Samus||samus||mario||||Link");

    //typedef find_iterator<string::iterator> string_find_iterator;

    //string_find_iterator pos, end;
    //for (pos = make_find_iterator(str, first_finder("samus", is_iequal()));
    //        pos != end; ++pos)
    //{   cout << "[" << *pos << "]" ;    }

    auto pos = make_find_iterator(str, first_finder("samus", is_iequal()));
    decltype(pos) end;
    for(; pos != end; ++pos)
    {   cout << "[" << *pos << "]" ;    }

    cout << endl;

    typedef split_iterator<string::iterator> string_split_iterator;

    string_split_iterator p, endp;
    for (p = make_split_iterator(str, first_finder("||", is_iequal()));
            p != endp;  ++p)
    {   cout << "[" << *p << "]" ;  }
    cout << endl;
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
    case9();
    case10();
}

