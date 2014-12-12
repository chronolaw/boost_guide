// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#define BOOST_ASIO_DISABLE_STD_CHRONO
//#define BOOST_ASIO_ENABLE_HANDLER_TRACKING
#include <boost/function.hpp>
#include <boost/asio.hpp>
using namespace boost::asio;
using namespace boost::system;
//////////////////////////////////////////
void case1()
{
    ip::address addr;
    addr = addr.from_string("127.0.0.1");
    assert(addr.is_v4());
    cout << addr.to_string() << endl;
    addr = addr.from_string("ab::12:34:56");
    assert(addr.is_v6());

}
//////////////////////////////////////////
void case2()
{
    ip::address addr;
    addr = addr.from_string("127.0.0.1");
    ip::tcp::endpoint ep(addr, 6688);
    assert(ep.address() == addr);
    assert(ep.port() == 6688);
}

int main()
try
{
    case1();
    case2();
    //return 0;

    typedef ip::tcp::acceptor acceptor_type;
    typedef ip::tcp::endpoint endpoint_type;
    typedef ip::tcp::socket socket_type;

    cout << "server start." << endl;
    io_service io;

    acceptor_type acceptor(io,
            endpoint_type(ip::tcp::v4(), 6688));
    cout << acceptor.local_endpoint().address() << endl;

    for(;;)
    {
        socket_type sock(io);

        acceptor.accept(sock);

        cout << "client:";
        cout << sock.remote_endpoint().address() << endl;

        sock.send(buffer("hello asio"));
    }
}
catch (std::exception& e)
{
    cout << e.what() << endl;
}


