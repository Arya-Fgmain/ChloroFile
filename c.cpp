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

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(10000ms);

    if (c.Connect())
    {
        c.Reading();
        std::cout << "Connected to the server" << std::endl;
    }
    else
    {
        std::cout << "Didn't connect.\n";
    }




    std::cin.get();
    return 0;
}
