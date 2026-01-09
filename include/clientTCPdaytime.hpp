#pragma once
#include "clientTCP.hpp"

namespace bh {

/**
 * @brief A TCP client for the Daytime Protocol (RFC 867).
 * 
 * This class extends ClientTCP to provide daytime client functionality.
 * The client connects to a daytime server, receives the current date and time
 * in human-readable format, and displays it.
 * 
 * The Daytime Protocol is a simple protocol where:
 * 1. Client connects to server (typically port 13)
 * 2. Server sends current date/time and closes connection
 * 3. Client reads and displays the response
 * 
 * Example usage:
 * @code
 * bh::ClientTCPdaytime client;
 * client.connect("129.6.15.28", 13);
 * client.run();  // Receives and displays time
 * @endcode
 */
class ClientTCPdaytime : public ClientTCP {
public:
    /**
     * @brief Inherits constructors from ClientTCP.
     * 
     * Allows ClientTCPdaytime to be constructed using the same
     * constructors as the base ClientTCP class.
     */
    using ClientTCP::ClientTCP;
    
    /**
     * @brief Receives and displays the daytime response from the server.
     * 
     * Reads the date/time string sent by the server and displays it
     * to standard output. The server typically sends the time in the
     * format: "Day Mon DD HH:MM:SS YYYY\r\n" and then closes the connection.
     * 
     * This method should be called after successfully connecting to a
     * daytime server using the connect() method.
     * 
     * @note This method reads up to 127 characters from the server.
     * @note The connection should be established before calling this method.
     */
    void run();
};

}
