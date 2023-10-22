#include "general.h"
#include "client.h"


#define ASIO_STANDALONE

#include "asio.hpp"
// memory movement
#include "asio/ts/buffer.hpp"
// network comms
#include "asio/ts/internet.hpp"


int main()
{
    std::cout << "Client started.\n";
    Client c;

    if (c.Connect())
    {
        c.Reading();
        std::cout << "Connected to the server" << std::endl;
        
        // Implement message sending and receiving logic here
    }
    else
    {
        std::cout << "Didn't connect.\n";
    }

    // using namespace std::chrono_literals;
    // std::this_thread::sleep_for(10000ms);



    std::cin.get();
    return 0;
}

// int main()
// {
//     asio::error_code ec;

//     asio::io_context context;

//     asio::ip::tcp::socket socket(context);

//     // set up server on this computer
//     asio::ip::tcp::endpoint endpoint(asio::ip::make_address("127.0.0.1", ec), 80);

//     socket.connect(endpoint);

//     while (1)
//         std::cout << "waiting\n";

    



//     return 0;
// }