#if !defined(SERVER_H)
#define SERVER_H

#define ASIO_STANDALONE

#include "asio.hpp"
// memory movement
#include "asio/ts/buffer.hpp"
// network comms
#include "asio/ts/internet.hpp"

#include "general.h"
#include "queue.h"

// forward-declare client class for now
class Client;

class Server
{
    bool connected{false};
    std::vector<asio::ip::tcp::socket> clients;

    // order of declaration is important -- it is also the order of initialization
	asio::io_context asioCon; // shared amongst all clients
    asio::io_context::work someWork{asioCon};

	std::thread thContext = std::thread(
        [&] ()
        {
            asioCon.run();
        }
    );
			
	// these things need an asio context --> gets sockets of connected clients
	asio::ip::tcp::acceptor acp;

    public:

    Server() : acp(asioCon, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 10000))
    {
        
        // intializer with list initialization
    }

    void AcceptConnections()
    {
        std::cout << "got here.\n";

        acp.async_accept(
            [this] (asio::error_code error, asio::ip::tcp::socket socket)
            {
                if (!error)
                {
                    std::cout << "connected! " << socket.remote_endpoint() << '\n';
                    connected = true;
                }
                else
                {
                    std::cout << "couldn't connect " << error.message() << '\n'; 
                }

                AcceptConnections();
            }
        );
        
    }

    bool Connected()
    {
        return connected;
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
        
        asioCon.stop();
        acp.close();
        // thContext.join();
    };

};


#endif