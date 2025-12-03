#include "serverTCP.hpp"
#include <iostream>
#include <arpa/inet.h>

namespace bh {

    ServerTCP::ServerTCP(uint16_t port) : m_socket(AF_INET, SOCK_STREAM, 0), m_port(port) {
        struct sockaddr_in servaddr;
        std::memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(port);

        bind((SA*)&servaddr, sizeof(servaddr));
        listen(LISTENQ);
    }
    
    void ServerTCP::bind(const struct sockaddr *myaddr, socklen_t addrlen) {
        if (::bind(m_socket.getDescriptor(), myaddr, addrlen) < 0)
            throw std::runtime_error("TCPServer bind error: " + std::string(std::strerror(errno)));
    }

    void ServerTCP::listen(int backlog) {
        if (::listen(m_socket.getDescriptor(), backlog) < 0)
            throw std::runtime_error("TCPServer listen error: " + std::string(std::strerror(errno)));
    }

    int ServerTCP::accept(struct sockaddr *cliaddr, socklen_t *addrlen) {
        int connfd = ::accept(m_socket.getDescriptor(), cliaddr, addrlen);
        if (connfd < 0)
            throw std::runtime_error("TCPServer accept error: " + std::string(std::strerror(errno)));
        return connfd;
    }

    uint16_t ServerTCP::getPort() const {
        return m_port;
    }

    void ServerTCP::connectionServiced() {
        std::cout << "Connection serviced." << std::endl;
    }

    void ServerTCP::logConnection(const struct sockaddr_in& cliaddr) {
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &cliaddr.sin_addr, client_ip, INET_ADDRSTRLEN);
        uint16_t client_port = ntohs(cliaddr.sin_port);
        
        std::cout << "Connection from " << client_ip << ":" << client_port << std::endl;
    }

    std::ostream& operator<<(std::ostream& os, const ServerTCP& srv) {
        os << "TCPServer(port=" << srv.getPort() << ")";
        return os;
    }

}