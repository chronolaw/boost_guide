// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#define BOOST_ASIO_DISABLE_STD_CHRONO
//#define BOOST_ASIO_ENABLE_HANDLER_TRACKING
#include <boost/asio.hpp>
//#include <boost/asio/use_future.hpp>
using namespace boost::asio;
using namespace boost::system;

//////////////////////////////////////////
int main()
{
    for (int i = 0;i < 5;++i)
    {
        ip::tcp::iostream tcp_stream("127.0.0.1", "6688");
        string str;
        getline(tcp_stream,str);
        cout << str << endl;
    }
}

