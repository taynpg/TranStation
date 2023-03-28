#include "server.h"

namespace transfer {

tran_server::tran_server(asio::io_context& io_context,
    const asio::ip::tcp::endpoint& endpoint):
    acceptor_(io_context, endpoint)   
{

}

tran_server::~tran_server() {


}

void tran_server::do_accept() {


}

}