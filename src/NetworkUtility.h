#ifndef NETWORK_UTILITY
#define NETWORK_UTILITY

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

class NetworkUtility
{

    public:
        enum TYPE {
            SERVER, CLIENT
        };

        enum PROTOCOL {
            TCP, UDP
        };
        NetworkUtility();
        ~NetworkUtility();
        void SetState(TYPE type);
        void OpenSocket(PROTOCOL protocol);
        void Connect(std::string ip_address, unsigned int port);
        int Send(const std::string message);
        void Disconnect();
        bool IsEnabled();
        // void Bind(std::string ip_address, unsigned int port);
        // void Listen(unsigned int backlog);
        // void Recv(char* buf);


    private:
        bool isEnabled;
        int socketFD;
        PROTOCOL protocol;
        TYPE type;
        sockaddr_in server_address;
    
};

#endif // NETWORK_UTILITY

/*
TCP SERVER
- create socket
- bind to addr + port
- listen
- accept
- recv/send

TCP CLIENT
- create socket
- connect to addr + port
- send/recv

UDP SERVER
- create socket
- bind to addr + port
- send/recv

UDP CLIENT
- create socket
- connect (?)
- send/recv
*/