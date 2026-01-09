#pragma once
#include "serverTCP.hpp"


namespace bh {

    /**
     * @brief A TCP server implementing the Daytime Protocol (RFC 867).
     * 
     * This class extends ServerTCP to provide daytime service functionality.
     * The server accepts client connections, sends the current date and time
     * in human-readable format, and immediately closes the connection.
     * 
     * The Daytime Protocol operates on port 13 (both TCP and UDP), though
     * any port can be used. The server responds with the current date and time
     * in the format: "Weekday, Month Day Year HH:MM:SS-ZONE".
     * 
     * Example usage:
     * @code
     * bh::ServerTCPdaytime server(13);  // Create server on port 13
     * server.bind(...);
     * server.listen(LISTENQ);
     * server.daytimeService();  // Start serving clients
     * @endcode
     */
    class ServerTCPdaytime : public ServerTCP {
    public:
        /**
         * @brief Inherits constructors from ServerTCP.
         * 
         * Allows ServerTCPdaytime to be constructed using the same
         * constructors as the base ServerTCP class.
         */
        using ServerTCP::ServerTCP;
        
        /**
         * @brief Runs the daytime service in an infinite loop.
         * 
         * This method continuously accepts incoming client connections,
         * sends the current system date and time to each client,
         * and immediately closes the connection. The server runs indefinitely
         * until interrupted or an error occurs.
         * 
         * The date/time format sent to clients follows the C standard library
         * ctime() format: "Day Mon DD HH:MM:SS YYYY\r\n"
         * 
         * Calls onServerStart() before entering the main loop,
         * and connectionServiced() (non-virtual base class method) after 
         * handling each client connection.
         * 
         * @note This is a blocking operation that runs in an infinite loop.
         * @note Each connection is handled synchronously - one at a time.
         * 
         * @throws std::runtime_error If accept() or other socket operations fail.
         */
        void run() override;
        
        /**
         * @brief Called when the daytime server starts listening for connections.
         * 
         * Override this method to implement custom behavior when the server
         * begins operation, such as logging startup messages or initializing
         * resources specific to the daytime service.
         */
        void onServerStart() override;      
    };
}