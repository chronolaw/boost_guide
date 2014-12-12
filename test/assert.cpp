// Copyright (c) 2015
// Author: Chrono Law
#include <cstring>
#include <std.hpp>
using namespace std;

//#define BOOST_DISABLE_ASSERTS
#define BOOST_ENABLE_ASSERT_HANDLER
#include <boost/assert.hpp>

//////////////////////////////////////////

double func(int x)
{
    BOOST_ASSERT_MSG(x != 0, "divided by zero");
    return 1.0 / x;
}

double func2(int x)
{
    BOOST_ASSERT(x != 0 && "divided by zero");
    cout << "after BOOST_ASSERT" << endl;

    assert(x != 0 && "divided by zero");
    cout << "after" << endl;

    return 1.0 / x;
}

void case1()
{
    BOOST_ASSERT(16 == 0x10);
    //BOOST_ASSERT(string().size() == 1);

    func(0);
    //func2(0);

    int len;
    BOOST_VERIFY(len = strlen("123"));
    assert(len == 3);
}

//////////////////////////////////////////

#include <boost/format.hpp>
namespace boost {
void    assertion_failed(char const*, char const*, char const*, long) {}
void assertion_failed_msg(char const * expr, char const * msg, 
                        char const * function, 
                        char const * file, long line)
{
    boost::format fmt("Assertion failed!\nExpression: %s\n"
                      "Function: %s\nFile: %s\nLine: %ld\n"
                      "Msg: %s\n\n");
    fmt % expr% function% file% line %msg;
    cout << fmt;
}
}

int main()
{
    case1();
}

