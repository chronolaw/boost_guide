// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/test/execution_monitor.hpp>
#include <boost/test/utils/basic_cstring/io.hpp>
using namespace boost;

//////////////////////////////////////////

int f()
{
    cout << "f execute." << endl;
    throw "a error accoured";
    return 10;
}

void case1()
{
    execution_monitor em;
    try
    {
        //em.execute(unit_test::callback0<int>(f));
        em.execute(f);
    }
    catch (execution_exception& e)
    {
        cout << "execution_exception" << endl;
        //cout << e.what().begin()<< endl;
        cout << e.what()<< endl;
    }
}

//////////////////////////////////////////

struct my_error
{
    int err_code;
    my_error(int ec):err_code(ec){}
};

void translate_my_err(const my_error& e)
{
    cout << "my err = " << e.err_code << endl;
}

int g()
{
    cout << "g execute." << endl;
    throw my_error(100);
    return 0;
}

void case2()
{
    execution_monitor em;

    em.register_exception_translator<my_error>(&translate_my_err);
    try
    {
        em.execute(g);
    }
    catch (const execution_exception& e)
    {
        cout << "execution_exception" << endl;
        cout << e.what().begin();
    }
}

int main()
{
    case1();
    case2();
}
