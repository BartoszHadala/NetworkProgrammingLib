#pragma once
#include "clientTCP.hpp"

namespace bh {

/**
 * @brief A TCP client for the Echo Protocol (RFC 862).
 *
 * This class extends ClientTCP to provide echo client functionality.
 * The client connects to an echo server, sends data and
 * reads back the same data echoed by the server.
 *
 * The Echo Protocol traditionally uses port 7, but any port may be used.
 * Typical interaction is:
 * 1. Client connects to server (e.g., port 7)
 * 2. Client sends data to the server
 * 3. Server echoes the received data back to the client
 * 4. Client reads the echoed data and closes the connection when done
 *
 * Example usage:
 * @code
 * bh::ClientTCPecho client;
 * client.connect("127.0.0.1", 7);
 * // send data using write()/send() on client socket (or implement a helper)
 * client.run();  // Reads echoed data from server and prints it
 * @endcode
 */
class ClientTCPecho : public ClientTCP {
public:
    /**
     * @brief Inherits constructors from ClientTCP.
     * 
     * Allows ClientTCPecho to be constructed using the same
     * constructors as the base ClientTCP class.
     */
    using ClientTCP::ClientTCP;
    
    /**
     * @brief Reads echoed data from the server and displays it.
     *
     * After a successful connection (and optionally sending data), this
     * method reads data sent back by the echo server and writes it to
     * standard output. It continues reading until the server closes
     * the connection or an error occurs.
     *
     * @note The connection should be established before calling this method.
     */
    void run();
};

}
