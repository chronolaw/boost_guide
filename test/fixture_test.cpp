// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/test/unit_test.hpp>
#include <boost/assign.hpp>
using namespace boost;

//////////////////////////////////////////

struct global_fixture
{
    global_fixture(){cout << ("global setup\n");}
    ~global_fixture(){cout << ("global teardown\n");}
};

BOOST_GLOBAL_FIXTURE(global_fixture);

struct assign_fixture
{
    assign_fixture()
    {cout << ("suit setup\n");}
    ~assign_fixture()
    {cout << ("suit teardown\n");}

    vector<int> v;
};

BOOST_FIXTURE_TEST_SUITE(s_assign, assign_fixture)

BOOST_AUTO_TEST_CASE(t_assign1)
{
    using namespace boost::assign;

    v += 1,2,3,4;
    BOOST_CHECK_EQUAL(v.size(), 4);
    BOOST_CHECK_EQUAL(v[2], 3);
}

BOOST_AUTO_TEST_CASE(t_assign2)
{
    using namespace boost::assign;

    push_back(v)(10)(20)(30);

    BOOST_CHECK_EQUAL(v.empty(), false);
    BOOST_CHECK_LT(v[0], v[1]);
}

BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////
#include <boost/lexical_cast.hpp>
#include <boost/mpl/list.hpp>


BOOST_AUTO_TEST_SUITE(s_lexical_cast)

typedef mpl::list<short, int, long> types;
BOOST_AUTO_TEST_CASE_TEMPLATE(t_lexical_cast, T, types)
{
        T n(20);
            BOOST_CHECK_EQUAL(lexical_cast<string>(n), "20");
}

BOOST_AUTO_TEST_SUITE_END()

