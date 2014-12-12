// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/logic/tribool.hpp>
#include <boost/logic/tribool_io.hpp>
using namespace boost;

//////////////////////////////////////////
void case1()
{
    tribool tb(true);
    tribool tb2(!tb);

    if (tb)
    {   cout << "true" << endl; }

    tb2 = indeterminate;
    assert(indeterminate(tb2));
    cout << "tb2 = " << tb2 << endl;

    if (tb2 == indeterminate)
    {   cout << "indeterminate" << endl;    }

    if (indeterminate(tb2))
    {   cout << "indeterminate" << endl;    }

    cout << (tb2 || true )<< endl;
    cout << (tb2 && false )<< endl;

}

//////////////////////////////////////////
void case2()
{
    tribool tb(indeterminate);

    if (tb)
        cout << "never reach here" << endl;
    if (!tb)
        cout << "never reach here" << endl;

    if (indeterminate(tb))
        cout << "indeterminate" << endl;
}

//////////////////////////////////////////
BOOST_TRIBOOL_THIRD_STATE(unknown)

namespace tmp_ns
{
        BOOST_TRIBOOL_THIRD_STATE(unknown)
};


void case3()
{
    tribool tb(tmp_ns::unknown);
    assert(unknown(tb));
    assert(unknown(tb || false));

}

//////////////////////////////////////////
#include <boost/optional.hpp>
using namespace boost;

void case4()
{
    optional<bool> b;

    if (!b)
    {   cout << "indeterminate" << endl;    }

    b = false;
    if (b)
    {   cout << "b=" << *b << endl; }

    if (!b)
    {   cout << "false" << endl;    }

    if (b && !*b)
    {   cout << "real false" << endl;    }

}

//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
    case4();
}
