#pragma once
#include <sys/socket.h>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <cerrno>
#include <iostream>

/**
 * @namespace bh
 * @brief Namespace used throughout the project.
 */

namespace bh {

/**
 * @brief Base class representing a network socket descriptor.
 *
 * Encapsulates creation and lifetime of a file descriptor created by ::socket().
 * Derived classes can use m_sockfd for specific protocols (TCP, UDP, etc.).
 */
class Socket {
public:
    /**
     * @brief Creates a socket descriptor with the given parameters.
     * @param family   Address family: AF_INET, AF_INET6, AF_LOCAL, AF_ROUTE, AF_KEY.
     * @param type     Type: SOCK_STREAM, SOCK_DGRAM, SOCK_SEQPACKET, SOCK_RAW.
     * @param protocol Protocol: IPPROTO_TCP, IPPROTO_UDP, IPPROTO_SCTP, or 0 for default.
     * @throws std::runtime_error if socket creation fails.
     */
    Socket(int family, int type, int protocol);

    /**
     * @brief Closes the underlying descriptor.
     *
     * If the descriptor is valid (non-negative), this function calls ::close(m_sockfd)
     * and resets the descriptor to -1. It is safe to call multiple times.
     * 
     * @throws std::runtime_error if closing the socket fails.
     */
    void close();

    /**
     * @brief Closes the underlying descriptor.
     *
     * Equivalent to calling close() in the destructor.
     */
    ~Socket();

    /**
     * @brief Returns the underlying descriptor.
     * @return File descriptor associated with this socket.
     */
    int getDescriptor() const;

protected:
    /// Underlying file descriptor.
    int m_sockfd;
};

}