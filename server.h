#if !defined(SERVER_H)
#define SERVER_H

#include "general.h"
#include "queue"

// forward-declare client class for now
class Client;

class Server
{

    std::vector<Client> clients;

    std::shared_ptr<asio::io_context> context;
    
    asio::io_context::work work;

    asio::ip::tcp::acceptor acp;

    
    Server() : work(*context), acp(
        *context, 
        asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 10000)
        ) // -> acceptor needs an endpoint & port later
    {
        /*
        upon initialization
        give 'fake' work to context
        associate socket with context
        */

        // start the context in its own thread
        thContext = {
            [*context] ()
            {
                (*context).run();
            }
        }
    };

    void AcceptConnections()
    {
        acceptor.async_accept(
            [this] (asio::error_code error, asio::ip::tcp::socket socket)
            {
                if (!error)
                { // if no errors found
                    // add to list of current active clients
                    clients.push_back(clients);
                }
                else
                {
                    std::cout << "error connecting with client...see below\n";
                    std::cout << error.message() << '\n';
                }

                AcceptConnection(); // async-recursively call the function again
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
        acceptor.close();
        context.stop();
    };

};


#endif