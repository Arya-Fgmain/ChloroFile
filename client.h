#if !defined(CLIENT_H)
#define CLIENT_H

#define ASIO_STANDALONE

#include "asio.hpp"
// memory movement
#include "asio/ts/buffer.hpp"
// network comms
#include "asio/ts/internet.hpp"

#include "general.h"
#include "queue.h"

class Client
{

    public:

    asio::error_code ec;
    asio::io_context context;

    asio::io_context::work someWork{context};
    std::thread thContext = std::thread(
        [&] ()
        {
            context.run();
        }
    );

    asio::ip::tcp::socket socket;

    asio::ip::tcp::endpoint endpoint;

    public:

    Client() : socket{context}, endpoint{asio::ip::make_address("127.0.0.1", ec), 10000}
    {
        if (ec)
        {
            std::cout << "bad IP " << ec.message() << '\n';
            socket.close();
            context.stop();
        }
        
    }

    bool Connect()
    {
        socket.connect(endpoint, ec);
        if (!ec)
        {
            std::cout << "connected to endpoint: " << socket.remote_endpoint() << '\n';
            return true;
        }
        else
        {
            std::cout << "connection failed " << ec.message() << '\n';
            return false;
        }
        
    }

    // void Reading()
    // {
    //     std::vector<char> message(5 * 1024);

    //     std::cout << "reading begun\n";
    //     socket.async_read_some(
    //         asio::buffer(message.data(), message.size()),
    //         [&] (asio::error_code ec, std::size_t bytesRead) {
    //             if (!ec)
    //             {
    //                 std::cout << bytesRead << " bytes read\n";
    //                 for (char c : message)
    //                     std::cout << c;
    //                 std::cout << '\n';

    //                 Reading();
                    
    //             }
    //             else if (ec == asio::error::eof)
    //             {
    //                 std::cout << "connection closed by server.\n";
                    
    //             }
    //             else
    //             {
    //                 std::cout << "error reading " << ec.message() << '\n';
    //             }                
    //         }
    //     );
    // }

    void Reading()
{
    std::vector<char> message(1024); // Adjust the buffer size as needed

    std::cout << "Reading begun" << std::endl;

    socket.async_read_some(
        asio::buffer(message.data(), message.size()),
        [&](asio::error_code ec, std::size_t bytesRead) {
            if (!ec)
            {
                std::cout << "Received " << bytesRead << " bytes: ";
                for (std::size_t i = 0; i < bytesRead; ++i)
                {
                    std::cout << message[i];
                }
                std::cout << std::endl;

                // Continue reading for more data
                Reading();
            }
            else if (ec == asio::error::eof)
            {
                std::cout << "Connection closed by server." << std::endl;
            }
            else
            {
                std::cout << "Error reading: " << ec.message() << std::endl;
            }
        }
    );
}

    // void KeepUpdating()
    // {
    //     while (1)
    //     {
    //         std::cout << "...";
    //     }
    // }

    virtual ~Client() {
        socket.close();
        context.stop();
        thContext.join();
    }

};

#endif 