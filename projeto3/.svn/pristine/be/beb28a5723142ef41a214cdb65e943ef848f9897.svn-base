
#ifndef __SocketClient__
#define __SocketClient__

#include <iostream>
#include <winsock2.h>

class SocketClient {
    
    SOCKET _sockfd;
    
public:
    
    SocketClient(std::string host, int port);
    
    std::string read();
    
    void write(std::string);
    
    ~SocketClient();
    
};

#endif 

