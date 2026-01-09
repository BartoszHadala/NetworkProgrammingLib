#include "clientTCPecho.hpp"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "usage: " << argv[0] << " <IPaddress> <port>\n";
        return 1;
    }

    try {
        bh::ClientTCPecho client;
        client.connect(argv[1], std::stoi(argv[2]));
        client.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}