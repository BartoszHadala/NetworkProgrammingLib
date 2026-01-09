#include <iostream>
#include <cstring>
#include "clientTCP.hpp"

int main(int argc, char **argv) {
    
    if (argc != 3) {
       std::cerr << "usage: " << argv[0] << " <IPaddress> <Port>\n";
       return 1; 
    }

    try {
        uint16_t port = std::stoi(argv[2]);
        
        bh::ClientTCP client;
        std::cout << "Connecting to " << argv[1] << ":" << port << "...\n";
        client.connect(argv[1], port);
        std::cout << "Connected successfully!\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}