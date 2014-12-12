// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/lexical_cast.hpp>

#define BOOST_ASIO_DISABLE_STD_CHRONO
//#define BOOST_ASIO_ENABLE_HANDLER_TRACKING
#include <boost/function.hpp>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace boost::system;

//////////////////////////////////////////

#include <boost/chrono.hpp>
using namespace boost::chrono;
seconds operator"" _s(unsigned long long n)
{
    return seconds(n);
}

milliseconds operator"" _ms(unsigned long long n)
{
    return milliseconds(n);
}
//////////////////////////////////////////
void resolve_connect(ip::tcp::socket &sock,
                    const char* name, int port)
{
    ip::tcp::resolver r(sock.get_io_service());
    ip::tcp::resolver::query q(name, boost::lexical_cast<string>(port));

    auto iter = r.resolve(q);
    decltype(iter) end;
    error_code ec = error::host_not_found;
    for ( ;ec && iter != end; ++iter)
    {
        sock.close();
        sock.connect(*iter,ec);
    }
    if (ec)
    {
        cout << "can't connect." << endl;
        throw system_error(ec);
    }
    cout << "connect success." << endl;
}

void case1()
try
{
    io_service io;
    ip::tcp::socket sock(io);
    resolve_connect(sock,"www.boost.org", 80);
    cout << sock.remote_endpoint() << endl;

    //ios.run();
}
catch (std::exception& e)
{
        cout << e.what() << endl;
};

//////////////////////////////////////////
#include <boost/asio/steady_timer.hpp>
void case2()
{
    io_service io;
    ip::tcp::socket sock(io);
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 6688);

    sock.async_connect(ep, [](const error_code&){});

    steady_timer t(io, 500_ms);
    t.async_wait([&](const error_code&){
            cout << "time expired" << endl;
            sock.close();
            });

    io.run();
    cout << "io stopped" << endl;
}

//////////////////////////////////////////

int main()
{
    case1();
    case2();
}
