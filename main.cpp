#include <string_view>
#include <thread>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <fstream>


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

void grab_data_async(asio::ip::tcp::socket &socket, std::vector<char> &v)
{
    // assuming socket is associated with a context and connected to an endpoint
    socket.async_read_some(
        asio::buffer(v.data(), v.size()),
        [&] (asio::error_code ec, std::size_t bytesRead)
        {
            if (!ec)
            {
                std::cout << "# bytes read: " << bytesRead << '\n';

                for (int i{0}; i < bytesRead; ++i)
                    std::cout << v[i];
                
                grab_data_async(socket, v);
            }
        }
    );
}

int main()
{
    

    asio::error_code ec;

    asio::io_context context;

    asio::io_context::work work(context);

    std::thread thContext( [&context] () {context.run();} );

    asio::ip::tcp::socket socket(context);

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("51.38.81.49", ec), 80);

    assertState(ec, "bad IP", "endpoint exists!");

    socket.connect(endpoint, ec);

    assertState(ec, "couldn't connect to endpoint", "connected!");

    std::string request =
			"GET /index.html HTTP/1.1\r\n"
			"Host: example.com\r\n"
			"Connection: close\r\n\r\n";

    std::vector<char> vBuffer(3 * 1024);
    grab_data_async(socket, vBuffer);

    socket.write_some(asio::buffer(request.data(), request.size()), ec);

    // socket.wait(socket.wait_read);   
    
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(20000ms);

    assertState(ec, "failed to write data via stream socket", "data written successfully!");
    
    // close the socket, stop the context
    socket.close();
    context.stop();

    if (thContext.joinable())
        thContext.join();
    

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(5000ms);

    std::size_t available{socket.available()};

    std::cout << available << " bytes available\n";

    if (available)
    {
        std::vector<char> vBuffer(available);
        socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);
        assertState(ec, "failed to write data into input buffer", "successfully wrote data to buffer!");

        for (char c : vBuffer)
            std::cout << c;
        
        std::cout << '\n';

    }

    return 0;
}