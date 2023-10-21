#define ASIO_STANDALONE

#include "asio.hpp"
#include "asio/ts/buffer.hpp"
#include "asio/ts/internet.hpp"

#include <iostream>


int main()
{
    asio::error_code ec;
    asio::io_context context;

    asio::ip::tcp::socket socket(context);

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec),80);

    if (ec)
        std::cout << "bad IP\n";
    else
        std::cout << "IP working\n";

    return 0;
}