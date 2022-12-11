#include "server.h"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

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

    HTTPServer::HTTPServer(const std::string &address, const std::string &port,
                           const std::string &doc_root, std::size_t thread_pool_size)
        : thread_pool_size_(thread_pool_size),
          signals_(io_service_), acceptor_(io_service_)
    {
        // Register to handle the signals that indicate when the server should exit.
        // It is safe to register for the same signal multiple times in a program,
        // provided all registration for the specified signal is made through Asio.
        signals_.add(SIGINT);
        signals_.add(SIGTERM);
#if defined(SIGQUIT)
        signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)
        signals_.async_wait(boost::bind(&HTTPServer::handle_stop, this));
        std::cout<<thread_pool_size_<<std::endl;
        boost::asio::ip::tcp::resolver resolver(io_service_);
        boost::asio::ip::tcp::resolver::query query(address, port);
        boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);

        acceptor_.open(endpoint.protocol());
        acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        acceptor_.bind(endpoint);
        acceptor_.listen();

        start_accept();
    }

    void HTTPServer::run()
    {
        std::cout<<"Running..."<<std::endl;
        std::vector<std::shared_ptr<std::thread>> threads(thread_pool_size_);
        std::cout<<threads.size()<<std::endl;
        for (size_t i = 0; i < threads.size(); i++)
        {
            std::shared_ptr<std::thread> thread(
                new std::thread(
                    boost::bind(&boost::asio::io_service::run, &io_service_)));
            threads[i] = thread;
        }

        for (size_t i = 0; i < threads.size(); i++) {
            if (threads[i]->joinable())
                threads[i]->join();
        }

    }

    /// Initiate an asynchronous accept operation.
    void HTTPServer::start_accept()
    {
        TCPConnect::ptr new_connection = TCPConnect::create(io_service_);

        acceptor_.async_accept(new_connection->socket(),
                               boost::bind(&HTTPServer::handle_accept, this, new_connection,
                                           boost::asio::placeholders::error));
    }

    /// Handle completion of an asynchronous accept operation.
    void HTTPServer::handle_accept(TCPConnect::ptr new_connection, const boost::system::error_code &e)
    {
        if (!e) {
            new_connection->start();
        }

        start_accept();
    }

    /// Handle a request to stop the server.
    void HTTPServer::handle_stop()
    {
        io_service_.stop();
    }
}

int main()
{
    try
    {
        boost::asio::io_service io_service;
        // server::TCPServer server(io_context);
        // io_context.run();
        server::HTTPServer server("localhost", "8989", ".", 2);
        server.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}