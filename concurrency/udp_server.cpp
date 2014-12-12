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
    cout << "udp server start." << endl;
    io_service io;

    ip::udp::socket sock(io,
            ip::udp::endpoint(ip::udp::v4(), 6699));

    for (;;)
    {
        char buf[1];
        ip::udp::endpoint ep;

        error_code ec;
        sock.receive_from(buffer(buf), ep, 0, ec);

        if (ec && ec != error::message_size)
        {   throw system_error(ec);}

        cout << "send to " << ep.address() << endl;
        sock.send_to(buffer("hello asio udp"), ep);
    }
}



