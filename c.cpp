#include <string_view>
#include <thread>
#include <cstdint>
#include <chrono>
#include <iostream>
#include <memory> // for using unique pointers


#define ASIO_STANDALONE

#include "asio.hpp"
// memory movement
#include "asio/ts/buffer.hpp"
// network comms
#include "asio/ts/internet.hpp"

int main()
{
    asio::error_code ec;

    asio::io_context context;

    asio::ip::tcp::socket socket(context);

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("127.0.0.1", ec), 80);

    socket.connect(endpoint);

    while (1)
        std::cout << "waiting\n";

    
    


    return 0;
}