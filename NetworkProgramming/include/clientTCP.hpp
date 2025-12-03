#pragma once
#include "socket.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>

namespace bh {

    /**
     * @brief A class representing a TCP client.
     * 
     * Encapsulates a TCP client socket that can connect to a remote server.
     * The client creates a socket and establishes a connection to a specified
     * server address and port.
     */
    class ClientTCP {
    public:
        /**
         * @brief Constructs a TCP client.
         * 
         * Creates a TCP socket (AF_INET, SOCK_STREAM) ready for connection.
         */
        ClientTCP();
        
        /**
         * @brief Connects to a remote server using IP address and port.
         * 
         * Creates the address structure internally and establishes a TCP connection.
         * Automatically handles the conversion from string IP to binary format.
         * 
         * Example:
         * @code
         * ClientTCP client;
         * client.connect("127.0.0.1", 8080);
         * @endcode
         * 
         * @param ip Server IP address as a string (e.g., "192.168.1.1" or "127.0.0.1").
         * @param port Server port number (e.g., 8080).
         * @throws std::runtime_error if IP conversion or connection fails.
         */
        void connect(const char* ip, uint16_t port);
        
    protected:
        /// Socket object for network operations.
        Socket m_socket;
    };

}