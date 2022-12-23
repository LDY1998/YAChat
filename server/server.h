#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include "database/conn.h"

using boost::asio::ip::tcp;

/**
 * @brief Datetime string function for testing only
 *
 * @return std::string
 */
std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

namespace server
{

    class TCPConnect : public boost::enable_shared_from_this<TCPConnect>
    {
    public:
        typedef boost::shared_ptr<TCPConnect> ptr;

        // Create a shared ptr of tcp connection with io_context
        static ptr create(boost::asio::io_context &io_context)
        {
            return ptr(new TCPConnect(io_context));
        }

        tcp::socket &socket()
        {
            return socket_;
        }

        void start();

    private:
        TCPConnect(boost::asio::io_context &io_context)
            : socket_(io_context)
        {
        }
        void handle_write(const boost::system::error_code & /*error*/,
                          size_t bytes /*bytes_transferred*/)
        {
        }
        tcp::socket socket_;
    };

    class TCPServer
    {
    public:
        TCPServer(boost::asio::io_context &io_context) : io_context_(io_context),
                                                         acceptor_(io_context, tcp::endpoint(tcp::v4(), PORT))
        {
            start_accept();
        }

    private:
        void start_accept()
        {
            TCPConnect::ptr new_connection = TCPConnect::create(io_context_);

            acceptor_.async_accept(new_connection->socket(),
                                   boost::bind(&TCPServer::handle_accept, this, new_connection,
                                               boost::asio::placeholders::error));
        }

        void handle_accept(TCPConnect::ptr new_connection,
                           const boost::system::error_code &error)
        {
            std::cout << "Handling connection..." << std::endl;
            if (!error)
            {
                new_connection->start();
            }

            start_accept();
        }
        boost::asio::io_context &io_context_;
        tcp::acceptor acceptor_;
        static const int PORT = 8989;
    };

    /// The top-level class of the HTTP server.
    class HTTPServer
        : private boost::noncopyable
    {
    public:
        /// Construct the server to listen on the specified TCP address and port, and
        /// serve up files from the given directory.
        explicit HTTPServer(const std::string &address, const std::string &port,
                        const std::string &doc_root, std::size_t thread_pool_size);

        /// Run the server's io_service loop.
        void run();

    private:
        /// Initiate an asynchronous accept operation.
        void start_accept();

        /// Handle completion of an asynchronous accept operation.
        void handle_accept(TCPConnect::ptr new_connection, const boost::system::error_code &e);

        /// Handle a request to stop the server.
        void handle_stop();

        /// The number of threads that will call io_service::run().
        std::size_t thread_pool_size_;

        /// The io_service used to perform asynchronous operations.
        boost::asio::io_service io_service_;

        /// The signal_set is used to register for process termination notifications.
        boost::asio::signal_set signals_;

        /// Acceptor used to listen for incoming connections.
        boost::asio::ip::tcp::acceptor acceptor_;

        /// The next connection to be accepted.
        // connection_ptr new_connection_;

        /// The handler for all incoming requests.
        // request_handler request_handler_;
    };
}
