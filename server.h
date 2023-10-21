#if !defined(SERVER_H)
#define SERVER_H

#include "general.h"
#include "queue"

// forward-declare client class for now
class Client;

class Server
{
    std::vector<Client> clients;

    // order of declaration is important -- it is also the order of initialization
	asio::io_context asioCon; // shared amongst all clients
	std::thread thContext;
			
	// these things need an asio context --> gets sockets of connected clients
	asio::ip::tcp::acceptor acp;

    Server() : acp(asioCon, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 80))
    {
        thContext = std::thread(
            [&] () {
                asioCon.run();
            }
        );
    }

    void AcceptConnections()
    {
        acp.async_accept(
            [this] (asio::error_code error, asio::ip::tcp::socket socket)
            {
                if (!error)
                { // if no errors found
                    // add to list of current active clients
                    // clients.push_back(new client socket);
                }
                else
                {
                    std::cout << "error connecting with client...see below\n";
                    std::cout << error.message() << '\n';
                }

                AcceptConnections(); // async-recursively call the function again
            }
        );
    }

    void MsgClient()
    {
    }

    void Broadcast()
    {
    }

    virtual ~Server() {
        acp.close();
        asioCon.stop();
    };

};


#endif