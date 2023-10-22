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

// to store the clients and their respective IDs (to use later)
struct cliSocket {
    int index;
    asio::ip::tcp::socket &socket;
};


class Server
{
    // bool connected{false};
    int index{0};
    std::vector<cliSocket> clients;

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

        acp.async_accept(
            [this] (asio::error_code error, asio::ip::tcp::socket socket)
            {
                if (!error)
                {
                    std::cout << "connected! " << socket.remote_endpoint() << '\n';
                    cliSocket newSock{index++, socket};
                    clients.push_back(newSock);
                    // connected = true;
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
        return clients.size() > 0;
    }

    void MsgClient(int id, std::string msg)
    {
        if (id >= 0 && id < clients.size())
        {
            clients[id].addMsg(msg);
        }
    }

    // void Broadcast()
    // {
    //     for (Client c : clients)
    //         c.push_front(msg);
    // }

    virtual ~Server() {
        
        asioCon.stop();
        acp.close();
        thContext.join();
    };

};


#endif