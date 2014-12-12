// Copyright (c) 2015
// Author: Chrono Law
#include <cstring>
#include <std.hpp>
using namespace std;

#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
using namespace boost;

template<typename T>
void print(T &tok)
{
    for (auto& x : tok)
    {   cout << "[" << x << "]";    }
    cout << endl;
}

//////////////////////////////////////////
void case1()
{
    string str("Link raise the master-sword.");

    tokenizer<> tok(str);

    print(tok);
    //for(auto& x: tok)
    //{   cout << "["<< x << "]";}
}

//////////////////////////////////////////
void case2()
{
    char str[] = "Link ;; <master-sword> zelda";

    char_separator<char> sep;


    tokenizer<char_separator<char>, char*> tok(str, str +strlen(str), sep);
    print(tok);

    tok.assign(str, str +strlen(str),
        char_separator<char>(" ;-", "<>"));
    print(tok);

    tok.assign(str, str +strlen(str),
        char_separator<char>(" ;-<>", "", keep_empty_tokens));
    print(tok);
}

//////////////////////////////////////////
void case3()
{
    string str = "id,100,name,\"mario\"";

    escaped_list_separator<char> sep;
    tokenizer<escaped_list_separator<char> > tok(str, sep);
    print(tok);
}

//////////////////////////////////////////
void case4()
{
    string str = "2233344445";
    int offsets[] = {2,3,4};

    offset_separator sep(offsets, offsets + 3, true, false);
    tokenizer<offset_separator> tok(str, sep);
    print(tok);

    tok.assign(str, offset_separator(offsets, offsets + 3, false));
    print(tok);

    str += "56667";
    tok.assign(str, offset_separator(offsets, offsets + 3, true, false));
    print(tok);

}

//////////////////////////////////////////
template<typename Func, typename  String = std::string>
struct tokenizer_wrapper
{
    //typedef typename Func::string_type String;
    typedef tokenizer<Func, typename String::const_iterator, String > type;
};

void case5()
{
    wstring str(L"Link mario samus");

    auto p = make_split_iterator(str, first_finder(L" ", is_iequal()));
    decltype(p) endp;

    for (; p != endp;  ++p)
    {       wcout << L"[" << *p << L"]" ;   }
    cout << endl;

    char_separator<wchar_t> sep(L" ");
    //tokenizer<char_separator<wchar_t>,wstring::const_iterator,
    //    wstring > tok(str, sep);
    tokenizer_wrapper<
        char_separator<wchar_t>,wstring>::type      tok(str, sep);


    for(auto& x : tok)
    {      wcout << L"["<< x << L"]";  }
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
}

