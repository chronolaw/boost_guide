// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

using namespace boost::asio;
using namespace boost::system;

//////////////////////////////////////////
int main()
{
    io_service io;

    //boost::asio::posix::stream_descriptor in(io, ::dup(STDIN_FILENO));
    typedef boost::asio::posix::stream_descriptor descriptor_type;
    descriptor_type in(io, STDIN_FILENO);
    vector<char> buf(30);

    //typedef void(handler_type)(const error_code&, std::size_t);

    //function<handler_type> handler =
    //    [&](const error_code& ec, std::size_t len){
    //        if(ec)
    //        {return;}
    //        //cout << "get some data" << endl;
    //        if(len < buf.size())
    //        {
    //            buf[len] = 0;
    //        }
    //        cout << buf.data();
    //        in.async_read_some(buffer(buf), handler);
    //        };

    //in.async_read_some(buffer(buf), handler);

    spawn(io,
        [&](yield_context yield)
        {
            for(;;)
            {
                error_code ec;
                auto len = in.async_read_some(buffer(buf), yield[ec]);

                if(ec)
                {return;}

                if(len < buf.size())
                {
                    buf[len] = 0;
                }

                cout << buf.data();
            }
        }
    );

    io.run();
}
