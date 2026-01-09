#include <iostream>
#include "serverTCP.hpp"

int main(int argc, char *argv[]) {
    
    uint16_t port;
    
    if (argc == 2) {
        port = std::stoi(argv[1]);
    } else {
        std::cout << "Enter port number: ";
        std::cin >> port;
    }
    
    try {
        bh::ServerTCP server(port);

        std::cout << server << std::endl;

        for (;;) {
            sockaddr_in cliaddr;
            socklen_t clilen = sizeof(cliaddr);

            int connfd = server.accept((sockaddr*)&cliaddr, &clilen);
           
            server.logConnection(cliaddr);
            server.connectionServiced();
            
            ::close(connfd);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}