
#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include "Types.h"

#include "Networking/Networking.h"
#include "GLFW/glfw3.h"

class UDPSocket;

class UDPClient
{
public:

	UDPClient(uint16_t Port);
	~UDPClient();

	void Update();

	bool m_isConnected = false;
private:
	void Receive();

	UDPSocket* m_socket;
	uint16_t m_port;
};

#endif // UDP_CLIENT_H