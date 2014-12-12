// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
using namespace boost::system;

//////////////////////////////////////////
class my_category : public error_category
{
public:
    virtual const char *name() const BOOST_SYSTEM_NOEXCEPT
    { return "myapp_category"; }

    virtual string message(int ev)const
    {
        string msg;
        switch(ev)
        {
            case 0:
                msg = "ok";break;
            default:
                msg = "some error";break;
        }
        return msg;
    }
};


void case1()
{
    my_category my_cat;
    error_code ec(10, my_cat);
    cout << ec.value() << ec.message() << endl;
    ec = error_code(10, system_category());
    cout << ec.value() << ec.message() << endl;

}

//////////////////////////////////////////
void case2()
{
    cout << system_category().name() << endl;

    error_code ec;
    assert(ec.value() == errc::success);
    assert(!ec);
    assert(ec.category() == system_category());

    ec.assign(3L, system_category());
    auto econd = ec.default_error_condition();
    assert(econd == ec);


    assert(econd == system_category().default_error_condition(3L));

    cout << ec.message() << endl;
    cout << econd.message() << endl;
    cout << econd.value() << endl;

}

//////////////////////////////////////////
void case3()
{
    try
    {
        throw system_error(error_code(5, system_category()));
    }
    catch (system_error& e)
    {
        cout << e.what();
    }
}


//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
}
