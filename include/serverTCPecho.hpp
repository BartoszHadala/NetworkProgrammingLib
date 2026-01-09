#pragma once
#include "serverTCP.hpp"


namespace bh {

    /**
     * @brief A TCP server implementing the Echo Protocol (RFC 862).
     * 
     * This class extends ServerTCP to provide echo service functionality.
     * The server accepts client connections, reads data sent by clients,
     * and echoes the same data to the client.
     * 
     * The Echo Protocol traditionally operates on port 7, though
     * any port can be used. The server simply echoes back any data it receives
     * from the client until the connection is closed.
     * 
     * Example usage:
     * @code
     * bh::ServerTCPecho server(7);  // Create server on port 7
     * server.bind(...);
     * server.listen(LISTENQ);
     * server.run();  // Start serving clients
     * @endcode
     */
    class ServerTCPecho : public ServerTCP {
    public:
        /**
         * @brief Inherits constructors from ServerTCP.
         * 
         * Allows ServerTCPecho to be constructed using the same
         * constructors as the base ServerTCP class.
         */
        using ServerTCP::ServerTCP;
        
        /**
         * @brief Runs the echo service in an infinite loop.
         * 
         * This method continuously accepts incoming client connections,
         * reads data sent by clients, and echoes the same data
         * to each client. The server runs indefinitely until interrupted
         * or an error occurs.
         * 
         * For each connection, the server reads data in chunks 
         * and immediately writes the same data back to the client.
         * This continues until the client closes the connection or sends EOF.
         * 
         * Calls onServerStart() before entering the main loop,
         * and connectionServiced() after handling each client connection.
         * 
         * @note This is a blocking operation that runs in an infinite loop.
         * @note Each connection is handled synchronously - one at a time.
         * 
         * @throws std::runtime_error If accept() or other socket operations fail.
         */
        void run() override;
        
        /**
         * @brief Called when the echo server starts listening for connections.
         * 
         * Override this method to implement custom behavior when the server
         * begins operation, such as logging startup messages or initializing
         * resources specific to the echo service.
         */
        void onServerStart() override;      
    };
}