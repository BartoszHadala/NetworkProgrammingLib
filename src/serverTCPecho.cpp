#include "serverTCPecho.hpp"

namespace bh {

    void ServerTCPecho::run() {
        
        for (;;) {
            sockaddr_in cliaddr;
            socklen_t clilen = sizeof(cliaddr);
            int connfd = accept((sockaddr*)&cliaddr, &clilen);

            logConnection(cliaddr);

            char buff[64];
            ssize_t n;
            while ((n = read(connfd, buff, sizeof(buff))) > 0)
                write(connfd, buff, n);
            ::close(connfd);
            connectionServiced();
        }
    }

    void ServerTCPecho::onServerStart() {
        std::cout << "Server echo is listening..." << std::endl;
    }

}