#ifndef _TS_SOCK_MATCH_HEADER
#define _TS_SOCK_MATCH_HEADER

#include "asio/ip/tcp.hpp"
#include "trans_buffer.hpp"
#include <list>

namespace transfer {

    struct one_connect {
        // style: client or server (0 client 1 server -1 none)
        int                     style;  
        asio::ip::tcp::socket   socker_;
    };

    class tran_match {
    public:
        tran_match();
        ~tran_match();
    private:
        // recive all connect message
        void recive_all();
        // parse all message
        void parse();
    private:
        std::list<one_connect>      m_allcon;
        data_buffer_v1<char>           m_allMessage;
    };
}

#endif