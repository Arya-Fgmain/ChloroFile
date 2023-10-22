#if !defined(SERVER_H)
#define SERVER_H

#include "general.h"
#include "queue.h"

// forward-declare client class for now
class Client;

class Server
{
    std::vector<asio::ip::tcp::socket> clients;

    // order of declaration is important -- it is also the order of initialization
	asio::io_context asioCon; // shared amongst all clients
	std::thread thContext;
			
	// these things need an asio context --> gets sockets of connected clients
	asio::ip::tcp::acceptor acp;

    public:

    Server() : acp{asioCon, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 10000)}, thContext{ [&] () {
                asioCon.run();
            }}
    {
        // intializer with list initialization
    }

    void AcceptConnections()
    {
        acp.async_accept(
            [this] (asio::error_code error, asio::ip::tcp::socket socket)
            {
                std::cout << "got here.\n";
                if (!error)
                { // if no errors found
                    std::cout << "connected to client!\n";
                }
                else
                {
                    std::cout << "error connecting with client...see below\n";
                    std::cout << error.message() << '\n';
                }
                std::cout << "got here.\n";
                AcceptConnections(); // async-recursively call the function again
            }
        );
    }

    bool Connected()
    {
        return clients.size() > 0;
    }

    // void MsgClient(std::string msg)
    // {
    //     client.push_front(msg);
    // }

    // void Broadcast()
    // {
    //     for (Client c : clients)
    //         c.push_front(msg);
    // }

    virtual ~Server() {
        acp.close();
        asioCon.stop();
        thContext.join();
    };

};


#endif