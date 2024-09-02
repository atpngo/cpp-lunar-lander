#include "NetworkUtility.h"
#include "arpa/inet.h"
#include <iostream>

NetworkUtility::NetworkUtility()
{
    protocol = TCP;
    type = CLIENT;
    isEnabled = false;
    socketFD = 0;
}


NetworkUtility::~NetworkUtility()
{
    Disconnect();
}


void NetworkUtility::SetState(TYPE type)
{
    type = type;
}

void NetworkUtility::OpenSocket(PROTOCOL protocol)
{
    if (socketFD != 0)
        Disconnect();
    protocol = protocol;
    socketFD = socket(AF_INET, protocol == TCP ? SOCK_STREAM : SOCK_DGRAM, 0);
}

void NetworkUtility::Connect(std::string ip_address, unsigned int port)
{
    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_addr.s_addr = inet_addr(ip_address.c_str());

    bool success = connect(socketFD, (struct sockaddr *)&server_address, sizeof(server_address)) == 0;
    // NOTE: you will have to change this if you want go into non-blocking sockets...
    isEnabled = success;

}

int NetworkUtility::Send(const std::string message)
{
    if (!isEnabled)
        return -1;

    int bytesSent = send(socketFD, (char *)message.c_str(), message.size(), 0);

    return bytesSent;
}

void NetworkUtility::Disconnect()
{
    close(socketFD);
}

bool NetworkUtility::IsEnabled()
{
    return isEnabled;
}