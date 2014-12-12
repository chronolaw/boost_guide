// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/xpressive/xpressive.hpp>
//#include <boost/xpressive/xpressive_dynamic.hpp>
using namespace boost;

#if 0
//////////////////////////////////////////

void case1()
{
    using namespace boost::xpressive;

    cregex reg = cregex::compile("a.c");

    assert( regex_match("abc", reg));
    assert( regex_match("a+c", reg));

    assert(!regex_match("ac", reg));
    assert(!regex_match("abd", reg));
}

//////////////////////////////////////////
void case2()
{
    using namespace boost::xpressive;

    cregex reg = cregex::compile(
            R"---(\d{6}(1|2)\d{3}(0|1)\d[0-3]\d\d{3}(X|\d))---",icase);

    assert( regex_match("999555197001019999", reg));
    assert( regex_match("99955519700101999X", reg));
    assert( regex_match("99955520100101999x", reg));

    assert(!regex_match("99955520100101999Z", reg));
    assert(!regex_match("99955530100101999X", reg));
    assert(!regex_match("999555201099019998", reg));
    assert(!regex_match("999555201012419991", reg));
}


//////////////////////////////////////////
void case3()
{
    using namespace boost::xpressive;

    cregex reg = cregex::compile(
            R"--(\d{6}((1|2)\d{3})((0|1)\d)([0-3]\d)(\d{3}(X|\d)))--",icase);
            //"\\d{6}((1|2)\\d{3})((0|1)\\d)([0-3]\\d)(\\d{3}(X|\\d))",icase);

    cmatch what;
    assert(regex_match("999555197001019999", what, reg));
    for (auto& x : what)
    {   cout << "[" << x << "]";    }
    cout << endl;

    cout << "date:"<< what[1] << what[3] << what[5] << endl;
}



//////////////////////////////////////////
void case4()
{
    using namespace boost::xpressive;

    string str("readme.txt");

    sregex start_reg = sregex::compile("^re.*");
    sregex end_reg = sregex::compile(".*txt$");

    assert(regex_match(str, start_reg));
    assert(regex_match(str, end_reg));

}


//////////////////////////////////////////
void case5()
{
    using namespace boost::xpressive;

    char str[] = "there is a POWER-suit item";
    cregex reg =cregex::compile("(power)-(.{4})", icase);

    assert(regex_search(str, reg));

    cmatch what;
    regex_search(str, what, reg);
    assert(what.size() == 3);

    cout << what[1] << what[2] << endl;
    assert(!regex_search("error message", reg));
}

//////////////////////////////////////////
void case6()
{
    using namespace boost::xpressive;

    string str("readme.TXT");

    sregex start_reg = sregex::compile("^re");
    sregex end_reg = sregex::compile("txt$",icase);

    assert(regex_search(str, start_reg));               //starts_with
    assert(regex_search(str, end_reg));                 //ends_with
    assert(regex_search(str, sregex::compile("me")));   //contains
}

//////////////////////////////////////////
void case7()
{
    using namespace boost::xpressive;

    string str("readme.txt");

    sregex reg1 = sregex::compile("(.*)(me)");
    sregex reg2 = sregex::compile("(t)(.)(t)");

    cout << regex_replace(str, reg1, "manual") << endl;
    cout << regex_replace(str, reg1, "$1you") << endl;
    cout << regex_replace(str, reg1, "$&$&") << endl;
    cout << regex_replace(str, reg2, "$1N$3") << endl;

    str = regex_replace(str, reg2, "$1$3");
    cout << str << endl;

    {
        string str("2010 Happy new Year!!!");

        sregex reg1 = sregex::compile("^(\\d| )*");
        sregex reg2 = sregex::compile("!*$");

        cout << regex_replace(str, reg1, "") << endl;
        cout << regex_replace(str, reg2, "") << endl;

        str = regex_replace(str, reg1, "Y2000 ");
        cout << str << endl;

    }
}


//////////////////////////////////////////
void case8()
{
    using namespace boost::xpressive;

    string str("Power-bomb, power-suit, pOWER-beam all items\n");

    sregex reg = sregex::compile("power-(\\w{4})", icase);

    sregex_iterator pos(str.begin(), str.end(), reg);
    sregex_iterator end;
    for(;pos != end;)
    {
        cout << "[" << (*pos)[0] << "]";
        ++pos;
    }
    cout << endl;
}

//////////////////////////////////////////
void case9()
{
    using namespace boost::xpressive;

    char str[] = "*Link*||+Mario+||Zelda!!!||Metroid";

    cregex reg = cregex::compile("\\w+", icase);

    cregex_token_iterator pos(str, str + strlen(str), reg);
    for(;pos != cregex_token_iterator();++pos)
    {
        cout << "[" << *pos << "]";
    }
    cout << endl;

    cregex split_reg = cregex::compile("\\|\\|");
    pos = cregex_token_iterator(str, str + strlen(str),
            split_reg, -1);
    for(;pos != cregex_token_iterator();++pos)
    {
        cout << "[" << *pos << "]";
    }
    cout << endl;
}


//////////////////////////////////////////

void case10()
{
    using namespace boost::xpressive;

    cregex_compiler rc;

    rc["reg1"] = rc.compile("a|b|c");
    rc["reg2"] = rc.compile("\\d*");

    assert(!regex_match("abc", rc["reg1"]));
    assert(regex_match("123", rc["reg2"]));

}

#endif

//////////////////////////////////////////
#include <boost/algorithm/string.hpp>

void case11()
{
    using namespace boost::xpressive;

    struct formater
    {
        string operator()(cmatch const &m)const
        {   return boost::to_upper_copy(m[0].str());    }
    };
    char str[] = "*Link*||+Mario+||Zelda!!!||Metroid";

    cregex reg = cregex::compile("\\w+", icase);
    cout << regex_replace(str, reg, formater()) << endl;
}

//////////////////////////////////////////
void case12()
{
    using namespace boost::xpressive;

    //const char *str2 = "123abc";
    auto str = "123abc";
    cregex reg = bos >> *_d >> +_w;
    assert(regex_match(str, reg));

}

//////////////////////////////////////////

int main()
{
    //case1();
    //case2();
    //case3();
    //case4();
    //case5();
    //case6();
    //case7();
    //case8();
    //case9();
    //case10();
    case11();
    case12();
}

