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

int main()
{
    

    asio::error_code ec;

    asio::io_context context;

    asio::io_context::work work(context);

    std::thread thContext( [&context] () {context.run();} );

    asio::ip::tcp::socket socket(context);

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 80);

    std::cout << "Everything is cool\n";

    socket.close();

    context.stop();

    return 0;
}