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
    cout << "client start." << endl;
    io_service io;

    ip::udp::endpoint send_ep(
            ip::address::from_string("127.0.0.1"), 6699);
    ip::udp::socket sock(io);
    sock.open(ip::udp::v4());

    char buf[1];
    sock.send_to(buffer(buf), send_ep);

    vector<char> v(100,0);
    ip::udp::endpoint recv_ep;
    sock.receive_from(buffer(v), recv_ep);
    cout << "recv from " << recv_ep.address() << " ";
    cout << &v[0] << endl;
}

