#pragma once

#include "Networking/Networking.h"
#include <string>
#include <iostream>

class UDPSocket
{
public:
    UDPSocket()
    {
        sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sock == INVALID_SOCKET)
            throw std::system_error(WSAGetLastError(), std::system_category(), "Error opening socket");
    }
    ~UDPSocket()
    {
        closesocket(sock);
    }

    void SendTo(const std::string& address, unsigned short port, const char* buffer, int len, int flags = 0)
    {
        sockaddr_in add;
        add.sin_family = AF_INET;
        add.sin_addr.s_addr = inet_addr(address.c_str());
        add.sin_port = htons(port);
        int ret = sendto(sock, buffer, len, flags, reinterpret_cast<SOCKADDR*>(&add), sizeof(add));
        if (ret < 0)
            throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
    }

    void SendTo(sockaddr_in& address, const char* buffer, int len, int flags = 0)
    {
        int ret = sendto(sock, buffer, len, flags, reinterpret_cast<SOCKADDR*>(&address), sizeof(address));
        if (ret < 0)
            throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
    }

    int RecvFrom(sockaddr_in& outFrom, char* buffer, int len, int flags = 0)
    {
        //check if anything to recv
        FD_SET readSet;
        FD_ZERO(&readSet);
        timeval timeout{ 0, 0 };

        //Add socket to the read set
        FD_SET(sock, &readSet);
        int result = select((int)sock, &readSet, NULL, NULL, &timeout);
        if (result == -1)
        {
            printf("select exited with result: %d\n", WSAGetLastError());
        }
        else if (result == 0)
        {
            //std::cout << "select exited with result: " << result << std::endl;
        }
        else
        {
            int size = sizeof(outFrom);
            int ret = recvfrom(sock, buffer, len, flags, reinterpret_cast<SOCKADDR*>(&outFrom), &size);
            if (ret < 0)
                return -1;

            // make the buffer zero terminated
            buffer[ret] = 0;
            return 1;
        }
        return 0;
    }

    void Bind(unsigned short port)
    {
        sockaddr_in add;
        add.sin_family = AF_INET;
        add.sin_addr.s_addr = htonl(INADDR_ANY);
        add.sin_port = htons(port);

        int ret = bind(sock, reinterpret_cast<SOCKADDR*>(&add), sizeof(add));
        if (ret < 0)
            throw std::system_error(WSAGetLastError(), std::system_category(), "Bind failed");
    }

private:
    SOCKET sock;
};

