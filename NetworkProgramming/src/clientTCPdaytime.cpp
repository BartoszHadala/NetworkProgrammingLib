#include "clientTCPdaytime.hpp"

namespace bh {

    void ClientTCPdaytime::run() {
        char recvline[128];
        ssize_t n = ::read(m_socket.getDescriptor(), recvline, sizeof(recvline) - 1);
        if (n < 0) {
            std::cerr << "read error\n";
            return;
        }
        recvline[n] = '\0';
        std::cout << "Daytime server response: " << recvline;
    }
}