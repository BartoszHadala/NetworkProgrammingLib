#pragma once
#include "socket.hpp"
#include <cinttypes>
#include <ostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

/**
 * @def SA
 * @brief Shorthand macro for struct sockaddr.
 * 
 * Simplifies casting between different socket address structures (sockaddr_in, sockaddr_in6)
 * and the generic sockaddr structure required by socket functions.
 */
#define SA struct sockaddr

/**
 * @def LISTENQ
 * @brief Maximum length of the queue of pending connections.
 * 
 * Defines the backlog parameter for the listen() function. This value specifies
 * the maximum number of pending connections that can be queued before the server
 * starts rejecting new connection attempts. Value of 2 is suitable for simple servers.
 */
#define LISTENQ   2

namespace bh {

    /**
     * @brief A class representing a TCP server.
     * Creates an address structure, binds it to a port using the bind function, listens for incoming connections, and accepts them. Allows the port to be listed.
     */
    class ServerTCP {
    public:
        /**
         * @brief Constructs a TCP server on the specified port.
         * 
         * Creates a TCP socket, binds it to the specified port on all interfaces (INADDR_ANY),
         * and sets it to listen for incoming connections.
         * 
         * @param port The port number on which the server will listen.
         * @throws std::runtime_error if socket creation, bind, or listen fails.
         */
        ServerTCP(uint16_t port);
        
        /**
         * @brief Binds the socket to a specific address.
         * 
         * Associates the socket with a specific IP address and port number.
         * The address structure must be properly initialized with the following fields:
         * - sin_family: Address family (AF_INET for IPv4, AF_INET6 for IPv6)
         * - sin_port: Port number in network byte order (use htons() to convert)
         * - sin_addr: IP address (use INADDR_ANY to bind to all interfaces, or inet_pton() for specific address)
         * 
         * Example for IPv4:
         * @code
         * struct sockaddr_in servaddr;
         * memset(&servaddr, 0, sizeof(servaddr));
         * servaddr.sin_family = AF_INET;
         * servaddr.sin_port = htons(8080);
         * servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
         * server.bind((SA*)&servaddr, sizeof(servaddr));
         * @endcode
         * 
         * @param myaddr Pointer to a sockaddr structure containing the address to bind to.
         * @param addrlen Length of the address structure.
         * @throws std::runtime_error if bind operation fails.
         */
        void bind(const struct sockaddr *myaddr, socklen_t addrlen);
        
        /**
         * @brief Sets the socket to listen for incoming connections.
         * @param backlog Maximum length of the queue of pending connections.
         * @throws std::runtime_error if listen operation fails.
         */
        void listen(int backlog);
        
        /**
         * @brief Accepts an incoming connection.
         * @param cliaddr Pointer to a sockaddr structure to store the client's address.
         * @param addrlen Pointer to the length of the client address structure.
         * @return File descriptor for the accepted connection.
         * @throws std::runtime_error if accept operation fails.
         */
        int accept(struct sockaddr *cliaddr, socklen_t *addrlen);
        
        /**
         * @brief Returns the port number on which the server is listening.
         * @return The port number.
         */
        uint16_t getPort() const;
        
        /**
         * @brief Outputs server information to a stream.
         * @param os Output stream.
         * @param srv TCP server instance.
         * @return Reference to the output stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const ServerTCP& srv);
        
        /**
         * @brief Virtual method to run the server.
         * 
         * This method should be overridden by derived classes to implement
         * specific server logic (e.g., daytime, echo, HTTP).
         */
        virtual void run() {} 

        /**
         * @brief Logs information after a client connection has been serviced.
         * 
         * This method provides default logging behavior that is
         * common to all server types. Called automatically after handling
         * each client request.
         */
        void connectionServiced();
        
        /**
         * @brief Logs information about an accepted client connection.
         * 
         * Displays the client's IP address and port number.
         * This method is called automatically after accepting a connection.
         * 
         * @param cliaddr Client address structure containing IP and port information.
         */
        void logConnection(const struct sockaddr_in& cliaddr);
        
        virtual ~ServerTCP() = default; 
        
    protected:
        /**
         * @brief Called when the server starts listening.
         * 
         * Override this method to implement custom logging or notification
         * when the server begins accepting connections.
         */
        virtual void onServerStart() {}
        
        
    private:
        /// Socket object for network operations.
        Socket m_socket;
        /// Port number on which the server listens.
        uint16_t m_port;        
    };

}