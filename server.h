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
#include "connection.h"

// to store the clients and their respective IDs (to use later)
// struct cliSocket {
//     int index;
//     asio::ip::tcp::socket &socket;
// };


class Server
{
    public:

    // bool connected{false};
    int index{0};
    // std::vector<cliSocket> clients;
    std::vector<Connection> clients;

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
                    // cliSocket newSock{index++, socket};
                    // clients.push_back(newSock);
                    
                    clients.push_back({index, socket});
                    ++index;
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
        

        std::cout << "function called!\n";
        if (id >= 0 && id < clients.size())
        {

            if (!clients[id].socket.is_open())
            {
                std::cout << "socket closed.\n";
                return;
            }
            else
            {
                asio::error_code ec;

                asio::write(
                    clients[id].socket,
                    asio::buffer(msg),
                    ec
                );

                if (ec)
                {
                    std::cout << "trouble sending message. " << ec.message() << '\n';
                }
                else
                    std::cout << "message has been sent!\n";
            }

            
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