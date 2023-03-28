#ifndef _TS_HANDLE_HEADER
#define _TS_HANDLE_HEADER

#include "asio/ip/tcp.hpp"
#include "trans_buffer.hpp"

namespace transfer {

    class trans_file {
    public:
        trans_file(asio::ip::tcp::socket& socketSend_, asio::ip::tcp::socket& socketRec_);
    public:
        void start();
    private:
        void read_data();
        void send_data();
    private:
        asio::ip::tcp::socket           m_socketSend;
        asio::ip::tcp::socket           m_socketRec;
        char                            m_temSend[1024];
        char                            m_temRec[1024];
        data_buffer_v1<char>            m_buffer;
    };
}

#endif