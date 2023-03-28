#include "trans_file.h"

namespace transfer {

trans_file::trans_file(asio::ip::tcp::socket& socketSend_,
    asio::ip::tcp::socket& socketRec_) :
    m_socketSend(std::move(socketSend_)),
    m_socketRec(std::move(socketRec_))
{
}

void trans_file::start() {

    read_data();
    send_data();
}

void trans_file::read_data() {

    m_socketSend.async_read_some(asio::buffer(m_temSend), 
    [this](std::error_code ec, std::size_t len){

        if (ec) {
            return ;
        }
        if (m_buffer.write(m_temSend, std::strlen(m_temSend))) {

        }
        read_data();
    });
}

void trans_file::send_data() {

    if (m_buffer.read(m_temRec, sizeof(m_temRec))) {

    }

    m_socketRec.async_write_some(asio::buffer(m_temRec), 
    [this](std::error_code ec, std::size_t len){

        if (ec) {
            return ;
        }
        read_data();
    });
}

}