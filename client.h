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
    NetQueue queue;

    asio::error_code ec;
    asio::io_context context;
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

    void addMsg(std::string item)
    {
        queue.push_back(item);
    }

    std::string readMsg(std::string item)
    {
        return queue.pop_front();
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
    }

};

#endif 