// Copyright (c) 2015
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#define BOOST_ASIO_DISABLE_STD_CHRONO
//#define BOOST_ASIO_ENABLE_HANDLER_TRACKING
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/asio.hpp>
using namespace boost::asio;
using namespace boost::system;

class client
{
    typedef client                        this_type;
    typedef ip::tcp::endpoint           endpoint_type;
    typedef ip::address               address_type;
    typedef ip::tcp::socket             socket_type;
    typedef shared_ptr<socket_type>   sock_ptr;
    typedef vector<char>                buffer_type;
private:
    io_service                          m_io;
    buffer_type                         m_buf;
    endpoint_type                       m_ep;
public:
    client():
        //m_buf(100,0),
        m_buf(5,0),
        m_ep(address_type::from_string("127.0.0.1"), 6688)
    {
        start();
    }

    void run()
    {
        m_io.run();
    }

    //void start()
    //{
    //    sock_ptr sock(new socket_type (m_io));
    //    sock->async_connect(m_ep,
    //            bind(&this_type::conn_handler,this,
    //                boost::asio::placeholders::error, sock));
    //}

    void start()
    {
        sock_ptr sock(new socket_type (m_io));

        //function<void(const error_code&,std::size_t)> handler =
        //    [this, sock, handler](const error_code& ec, std::size_t)
        //    {
        //        if (ec)
        //        {   return;     }
        //        cout << &m_buf[0] << endl;

        //        //sock->async_read_some(buffer(m_buf), handler);
        //    };

        sock->async_connect(m_ep,
            [this, sock](const error_code& ec)
            {
                if (ec)
                {   return;     }

                sock->async_read_some(buffer(m_buf), 
                    [this, sock](const error_code& ec,std::size_t)
                    {
                        read_handler(ec, sock);
                    }
                );
            }
        );
    }

    void conn_handler(const error_code& ec, sock_ptr sock)
    {
        if (ec)
        {   return;     }

        cout << "recive from " << sock->remote_endpoint().address();

        sock->async_read_some(buffer(m_buf),
                bind(&client::read_handler, this, 
                    boost::asio::placeholders::error,
                    //boost::asio::placeholders::bytes_transferred,
                    sock));

        //start();
    }
    void read_handler(const error_code& ec, /*std::size_t n,*/ sock_ptr sock)
    {
        if (ec)
        {   return;     }
        cout << &m_buf[0] << endl;

        sock->async_read_some(buffer(m_buf),
                bind(&client::read_handler, this, 
                    boost::asio::placeholders::error,
                    //boost::asio::placeholders::bytes_transferred,
                    sock));
    }
};


int main()
{
    cout << "client start." << endl;
    client cl;
    cl.run();

}
