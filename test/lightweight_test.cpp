// Copyright (c) 2015
// Author: Chrono Law
#include <type_traits>
#include <std.hpp>
using namespace std;

#include <boost/smart_ptr.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/core/lightweight_test_trait.hpp>
//using namespace boost;

int main()
{
    auto p = make_shared<int>(10);

    BOOST_TEST(*p == 10);
    BOOST_TEST(p.unique());

    BOOST_TEST_EQ(p.use_count(), 1);
    BOOST_TEST_NE(*p, 20);

    p.reset();
    BOOST_TEST(!p);

    //BOOST_TEST_THROWS(*p, std::runtime_error);
    //BOOST_ERROR("error accured!!");

    BOOST_TEST_TRAIT_TRUE((is_integral<int>));
    BOOST_TEST_TRAIT_FALSE((is_function<int>));

    return boost::report_errors();
}


