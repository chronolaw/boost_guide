// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#define BOOST_ASIO_DISABLE_STD_CHRONO
//#define BOOST_ASIO_ENABLE_HANDLER_TRACKING
#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
using namespace boost;
using namespace boost::asio;
using namespace boost::system;
//////////////////////////////////////////

class server
{
    typedef server this_type;
    typedef ip::tcp::acceptor     acceptor_type;
    typedef ip::tcp::endpoint   endpoint_type;
    typedef ip::tcp::socket   socket_type;
    typedef boost::shared_ptr<socket_type>     sock_ptr;

private:
    io_service m_io;
    acceptor_type m_acceptor;
public:
    server():
      m_acceptor(m_io,endpoint_type(ip::tcp::v4(), 6688))
    {   accept();    }

    void run()
    {
        m_io.run();
    }

private:
    //void accept()
    //{
    //    sock_ptr sock(new socket_type(m_io));

    //    m_acceptor.async_accept(*sock,
    //            bind(&this_type::accept_handler, this,
    //            boost::asio::placeholders::error, sock));
    //}

    void accept()
    {
        sock_ptr sock(new socket_type(m_io));

        m_acceptor.async_accept(*sock,
            [this, sock](const error_code& ec)
            {
                if (ec)
                {   return;     }

                sock->async_send(
                    buffer("hello asio"),
                    [](const error_code& ec, std::size_t)
                    {   cout << "send msg complete." << endl;   }
                    );

                accept();
            }
        );
    }

    void accept_handler(const error_code& ec, sock_ptr sock)
    {
        if (ec)
        {   return;     }

        cout << "client:";
        cout << sock->remote_endpoint().address() << endl;
        sock->async_write_some(buffer("hello asio"),
                bind(&this_type::write_handler2, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));

        accept();
    }

    void write_handler(const error_code&)
    {   cout << "send msg complete." << endl;   }

    void write_handler2(const error_code&, std::size_t n)
    {   cout << "send msg " << n << endl;   }
};


int main()
{
    server svr;
    svr.run();
}
