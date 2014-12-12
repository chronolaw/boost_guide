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

int main()
try
{
    typedef ip::tcp::endpoint endpoint_type;
    typedef ip::tcp::socket socket_type;
    typedef ip::address address_type;

    cout << "client start." << endl;

    io_service io;

    socket_type sock(io);
    endpoint_type ep(address_type::from_string("127.0.0.1"), 6688);

    sock.connect(ep);
    cout << sock.available() << endl;

    //vector<char> str(sock.available() + 1, 0);
    //sock.receive(buffer(str));
    //cout << "recive from " << sock.remote_endpoint().address();
    //cout << &str[0] << endl;

    vector<char> str(5,0);
    error_code ec;
    for(;;)
    {
        sock.read_some(buffer(str), ec);
        if(ec)
        {
            break;
        }
        cout << &str[0];
    }
    cout << endl;
}
catch (std::exception& e)
{
    cout << e.what() << endl;
}

