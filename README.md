# NetworkProgramming Library

A modern C++17 library for TCP network programming with protocol implementations.

## Overview

This library provides simple, clean, and well-documented C++ classes for TCP network communication:

### Core Classes
- **Socket** - Base socket class 
- **ServerTCP** - Generic TCP server with virtual methods for customization
- **ClientTCP** - Generic TCP client implementation

### Protocol Implementations
- **ServerTCPdaytime** - Daytime Protocol (RFC 867) server
- **ClientTCPdaytime** - Daytime Protocol (RFC 867) client

## Features

-  **Modern C++17** implementation
-  **Exception-based error handling** with detailed error messages
-  **IPv4 support** (IPv6 ready for future extensions)
-  **Polymorphic design** - virtual methods for protocol customization
-  **Clean and documented API** - Full Doxygen documentation
-  **Callback system** - `onServerStart()`, `logConnection()`, `connectionServiced()`

## Building

```bash
mkdir build
cd build
cmake ..
make
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

### Test with Public Time Server

```bash
./test_clientTCPdaytime 129.6.15.28 13
```

## Author

Bartosz Hadała - Network Programming Library Project

## References

- RFC 867 - Daytime Protocol: https://datatracker.ietf.org/doc/html/rfc867
- RFC 862 - Echo Protocol: https://www.rfc-editor.org/rfc/rfc862.html
- POSIX Socket API
- C++17 Standard
