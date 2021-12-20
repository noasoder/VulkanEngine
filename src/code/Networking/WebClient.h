
#ifndef WEB_CLIENT_H
#define WEB_CLIENT_H

#include <string>

#include "Networking/Networking.h"

class WebClient
{
public:

	WebClient(std::string url, std::string ext);
	~WebClient();

	bool	IsConnected() { return m_connected; };
	void	GetHTTP(const std::string url, const std::string ext);

private:

	int m_socket;
#ifdef WINDOWS
	addrinfo* result = 0, hints;
#endif // WINDOWS

	bool m_connected = false;
};

#endif // WEB_CLIENT_H