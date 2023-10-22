#if !defined(CONNECTION_H)
#define CONNECTION_H

#define ASIO_STANDALONE

#include "asio.hpp"
// memory movement
#include "asio/ts/buffer.hpp"
// network comms
#include "asio/ts/internet.hpp"

#include "general.h"
#include "queue.h"

struct Connection
{
    int index;
    asio::ip::tcp::socket &socket;
};

#endif