#include "general.h"
#include "server.h"

#define ASIO_STANDALONE

#include "asio.hpp"
// memory movement
#include "asio/ts/buffer.hpp"
// network comms
#include "asio/ts/internet.hpp"

int main()
{
    std::cout << "Server started.\n";
    Server s;
    s.AcceptConnections();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(10000ms);

    if (s.Connected())
        std::cout << "connected!\n";
    else
        std::cout << "not connected\n";

    std::cin.get();
    return 0;
}


// void acceptConnections(asio::ip::tcp::acceptor &acp)
// {

//     acp.async_accept(
//         [&] (asio::error_code error, asio::ip::tcp::socket socket)
//         {
//             if (!error)
//             {
//                 std::cout << "Connected!\n";
//                 std::cout << "endpoint: " << socket.remote_endpoint() << 'n';
//             }
//             else
//                 std::cout << "Connection Failed\n" << error.message() << '\n';

//             acceptConnections(acp);
//         }
//     );
    
// }

// int main()
// {
//     asio::error_code ec;
//     asio::io_context context;

//     asio::io_context::work work(context);

//     std::thread thContext {
//         [&context] () {
//             context.run();
//         }
//     };

//     asio::ip::tcp::acceptor acp(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 80));

//     while (1)
//         acceptConnections(acp);

//     return 0;
// }