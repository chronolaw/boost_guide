// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/exception/all.hpp>
using namespace boost;
//////////////////////////////////////////

class my_exception_test : public std::logic_error
{
    private:
        int err_no;
    public:
        my_exception_test(const char* msg, int err):
            std::logic_error(msg),err_no(err) {}
        int get_err_no()
        {   return err_no;}
};

struct my_exception :
    virtual std::exception,
    virtual boost::exception
{};

typedef boost::error_info<struct tag_err_no, int>     err_no;
typedef boost::error_info<struct tag_err_str, string> err_str;

//////////////////////////////////////////
void case1()
try
{
    try
    {

        throw my_exception() << err_no(10);
    }
    catch (my_exception& e)
    {

        cout << *get_error_info<err_no>(e)<<endl;
        cout << e.what()<<endl;
        e << err_str("other info");
        throw;
    }
}
catch(my_exception& e)
{
    cout << *get_error_info<err_str>(e) << endl;
}

//////////////////////////////////////////
#define DEFINE_ERROR_INFO(type, name) \
    typedef boost::error_info<struct tag_##name, type> name

void case2()
try
{
    throw my_exception() << errinfo_api_function("call api")
        << errinfo_errno(101);
}
catch (boost::exception& e)
{
    cout << *get_error_info<errinfo_api_function>(e);
    cout << *get_error_info<errinfo_errno>(e);
    cout << endl;
}

//////////////////////////////////////////
struct my_err{};

void case3()
{
    try
    {
        throw enable_error_info(my_err()) << errinfo_errno(10);
        throw enable_error_info(std::runtime_error("runtime"))
         << errinfo_at_line(__LINE__);

    }
    catch (boost::exception& e)
    {
        cout << *get_error_info<errinfo_errno>(e)<<endl;
    }
}


//////////////////////////////////////////
#include <boost/throw_exception.hpp>

void case4()
{
    try
    {
        throw enable_error_info(my_err()) 
            << errinfo_errno(101)
            << errinfo_api_function("fopen");
    }
    catch (boost::exception& e)
    {
        cout << diagnostic_information(e)<<endl;
    }

    try
    {
        BOOST_THROW_EXCEPTION(std::logic_error("logic"));
    }
    catch (boost::exception& e)
    {
        cout << diagnostic_information(e)<<endl;
    }
}

//////////////////////////////////////////

//////////////////////////////////////////

int main()
{
    case1();
    case2();
    case3();
    case4();
}


