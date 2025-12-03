# NetworkProgramming Library

A modern C++17 library for TCP network programming with protocol implementations.

## Overview

This library provides simple, clean, and well-documented C++ classes for TCP network communication:

### Core Classes
- **Socket** - Base socket class with RAII resource management
- **ServerTCP** - Generic TCP server with virtual methods for customization
- **ClientTCP** - Generic TCP client implementation

### Protocol Implementations
- **ServerTCPdaytime** - Daytime Protocol (RFC 867) server
- **ClientTCPdaytime** - Daytime Protocol (RFC 867) client

## Features

- ✅ **Modern C++17** implementation
- ✅ **Exception-based error handling** with detailed error messages
- ✅ **IPv4 support** (IPv6 ready for future extensions)
- ✅ **RAII resource management** - automatic socket cleanup
- ✅ **Polymorphic design** - virtual methods for protocol customization
- ✅ **Protocol implementations** - Daytime (RFC 867) included
- ✅ **Clean and documented API** - Full Doxygen documentation
- ✅ **Callback system** - `onServerStart()`, `logConnection()`, `connectionServiced()`

## Architecture

The library uses **composition** and **inheritance**:

### Inheritance Hierarchy
```
ClientTCP (base)
    └── ClientTCPdaytime

ServerTCP (base)
    └── ServerTCPdaytime
```

### Composition
Both `ClientTCP` and `ServerTCP` **contain** a `Socket` object (composition, not inheritance):
- `ClientTCP` has `m_socket` member (protected)
- `ServerTCP` has `m_socket` member (private)
- `Socket` provides RAII resource management for file descriptors

## Building

```bash
mkdir build
cd build
cmake ..
make
```

This will create:
- `libnetworklib.a` - Static library
- `test_serverTCP` - Generic TCP server example
- `test_clientTCP` - Generic TCP client example
- `test_serverTCPdaytime` - Daytime server example
- `test_clientTCPdaytime` - Daytime client example

## Usage Examples

### Generic TCP Server
```cpp
#include "serverTCP.hpp"

int main() {
    try {
        bh::ServerTCP server(8080);
        std::cout << server << " is listening..." << std::endl;
        
        for (;;) {
            sockaddr_in cliaddr;
            socklen_t clilen = sizeof(cliaddr);
            int connfd = server.accept((sockaddr*)&cliaddr, &clilen);
            
            server.logConnection(cliaddr);
            // Handle connection...
            ::close(connfd);
            server.connectionServiced();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

### Generic TCP Client
```cpp
#include "clientTCP.hpp"

int main() {
    try {
        bh::ClientTCP client;
        client.connect("127.0.0.1", 8080);
        
        // Send/receive data...
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

### Daytime Protocol Server (RFC 867)
```cpp
#include "serverTCPdaytime.hpp"

int main() {
    try {
        bh::ServerTCPdaytime server(13);
        server.run();  // Runs forever, serving time to clients
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

### Daytime Protocol Client (RFC 867)
```cpp
#include "clientTCPdaytime.hpp"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <IP> <port>\n";
        return 1;
    }
    
    try {
        bh::ClientTCPdaytime client;
        client.connect(argv[1], std::stoi(argv[2]));
        client.run();  // Receives and displays time
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

## Testing

### Test Daytime Protocol Locally

**Terminal 1 - Start server:**
```bash
./test_serverTCPdaytime 13000
```

**Terminal 2 - Run client:**
```bash
./test_clientTCPdaytime 127.0.0.1 13000
```

You should see the current date and time!

### Test with Public Time Server

```bash
./test_clientTCPdaytime 129.6.15.28 13
```

## Creating Custom Protocols

Extend `ServerTCP` or `ClientTCP` to implement your own protocols:

```cpp
class MyCustomServer : public bh::ServerTCP {
public:
    using ServerTCP::ServerTCP;
    
    void run() override {
        onServerStart();
        for (;;) {
            sockaddr_in cliaddr;
            socklen_t clilen = sizeof(cliaddr);
            int connfd = accept((sockaddr*)&cliaddr, &clilen);
            
            logConnection(cliaddr);
            
            // Your custom protocol logic here
            
            ::close(connfd);
            connectionServiced();
        }
    }
    
protected:
    void onServerStart() override {
        std::cout << "My custom server started!\n";
    }
};
```

## API Reference

Full API documentation is available in the Doxygen-generated documentation.

### Key Classes

- **Socket** - Low-level socket wrapper with automatic cleanup
- **ServerTCP** - Server base class with virtual `run()` method
- **ClientTCP** - Client base class for TCP connections
- **ServerTCPdaytime** - Complete Daytime protocol server implementation
- **ClientTCPdaytime** - Complete Daytime protocol client implementation

### Key Methods

- `ServerTCP::accept()` - Accept incoming connection
- `ServerTCP::logConnection()` - Log client IP and port
- `ServerTCP::connectionServiced()` - Log serviced connection
- `ClientTCP::connect()` - Connect to remote server
- Virtual `onServerStart()` - Override for custom server startup behavior
- Virtual `run()` - Override to implement protocol logic

## Error Handling

All methods throw `std::runtime_error` on failure with detailed error messages:

```cpp
try {
    bh::ServerTCP server(80);  // May fail if port in use
} catch (const std::runtime_error& e) {
    std::cerr << "Failed to create server: " << e.what() << '\n';
}
```

## Project Structure

```
NetworkProgramming/
├── include/           # Header files
│   ├── socket.hpp
│   ├── serverTCP.hpp
│   ├── clientTCP.hpp
│   ├── serverTCPdaytime.hpp
│   └── clientTCPdaytime.hpp
├── src/              # Implementation files
│   ├── socket.cpp
│   ├── serverTCP.cpp
│   ├── clientTCP.cpp
│   ├── serverTCPdaytime.cpp
│   └── clientTCPdaytime.cpp
├── examples/         # Example programs
│   ├── test_serverTCP.cpp
│   ├── test_clientTCP.cpp
│   ├── test_serverTCPdaytime.cpp
│   └── test_clientTCPdaytime.cpp
├── html/            # Generated documentation
├── CMakeLists.txt   # Build configuration
├── Doxyfile         # Documentation configuration
└── README.md        # This file
```

## License

See LICENSE file for details.

## Author

Bartosz Hadała - Network Programming Library Project

## References

- RFC 867 - Daytime Protocol: https://datatracker.ietf.org/doc/html/rfc867
- POSIX Socket API
- C++17 Standard
