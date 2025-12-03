#include "serverTCPdaytime.hpp"

namespace bh {

    void ServerTCPdaytime::run() {
        
        for (;;) {
            sockaddr_in cliaddr;
            socklen_t clilen = sizeof(cliaddr);
            int connfd = accept((sockaddr*)&cliaddr, &clilen);

            logConnection(cliaddr);

            time_t ticks = time(nullptr);
            char buff[64];
            snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
            ::write(connfd, buff, strlen(buff));
            ::close(connfd);
            connectionServiced();
        }
    }

    void ServerTCPdaytime::onServerStart() {
        std::cout << "Server Daytime is listening..." << std::endl;
    }

}