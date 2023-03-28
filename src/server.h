#ifndef _TS_SERVER_HEADER
#define _TS_SERVER_HEADER

#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"
#include <asio.hpp>
#include <queue>


namespace transfer {

    class tran_server {
    public:
        tran_server(asio::io_context& io_context,
            const asio::ip::tcp::endpoint& endpoint);
        ~tran_server();
    private:
        void do_accept();
    private:
        asio::ip::tcp::acceptor acceptor_;
    };
}

#endif