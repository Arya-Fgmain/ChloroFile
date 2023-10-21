#include <string_view>
#include <thread>
#include <cstdint>
#include <chrono>
#include <iostream>


#define ASIO_STANDALONE

#include "asio.hpp"
// memory movement
#include "asio/ts/buffer.hpp"
// network comms
#include "asio/ts/internet.hpp"

void assertState(asio::error_code ec, std::string_view errMessage, std::string_view succMessage)
{
    if (ec)
    {
        std::cout << errMessage << '\n';
        exit(0);
    }
    else
    {
        std::cout << succMessage << '\n';
    }
}

#include "net_queue.h"

int main()
{   
    NetQueue q;

    std::cout << q.size() << '\n';

    return 0;
}