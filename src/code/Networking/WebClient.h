#pragma once



#include <string>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "Ws2_32.lib")


class WebClient
{
public:

	WebClient(std::string url);
	~WebClient();

	bool	Connect();
	void	GetHTTP(const std::string url, const std::string ext);

private:

	SOCKET m_socket;

	struct addrinfo*	result = 0, hints;
};