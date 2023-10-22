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

    s.MsgClient(0, "Hello!");

    std::cin.get();
    return 0;
}

