#include "clientTCPecho.hpp"

namespace bh {

    void ClientTCPecho::run() {

    char sendline[MAXLINE], recvline[MAXLINE];

    while (std::cin.getline(sendline, MAXLINE)) {
        ssize_t n = write(m_socket.getDescriptor(), sendline, strlen(sendline));
        if (n < 0) {
            std::cerr << "write error\n";
            break;
        }
        n = read(m_socket.getDescriptor(), recvline, MAXLINE);
        if (n < 0) {
            std::cerr << "read error\n";
            break;
        }
        recvline[n] = '\0';
        std::cout << "Echo server respond: " << recvline << std::endl;
    }
    }
}