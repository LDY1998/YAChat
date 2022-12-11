#include "server.h"

namespace server
{
    void TCPConnect::start()
    {
        std::string message = make_daytime_string();
        std::cout << "Writing " << message << "..." << std::endl;

        boost::asio::async_write(socket_, boost::asio::buffer(message),
                                 boost::bind(&TCPConnect::handle_write, shared_from_this(),
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }
}

int main()
{
    try
    {
        boost::asio::io_context io_context;
        server::TCPServer server(io_context);
        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}