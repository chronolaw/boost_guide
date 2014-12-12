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
    io_service io;

    ip::tcp::endpoint ep(ip::tcp::v4(), 6688);
    ip::tcp::acceptor acceptor(io, ep);

    for (;;)
    {
        ip::tcp::iostream tcp_stream;
        acceptor.accept(*tcp_stream.rdbuf());
        tcp_stream << "hello tcp stream";
    }
}

