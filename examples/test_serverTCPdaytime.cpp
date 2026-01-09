#include "serverTCPdaytime.hpp"

int main(int argc, char **argv) {
    try {
        uint16_t port = 13;
        
        if (argc == 2) {
            port = std::atoi(argv[1]);
        }
        
        bh::ServerTCPdaytime server(port);
        std::cout << server << std::endl;
        server.onServerStart();
        server.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}