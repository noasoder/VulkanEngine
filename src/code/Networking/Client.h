
#ifndef CLIENT_H
#define CLIENT_H

#include "Utility/Types.h"

#include "Networking/Networking.h"
#include "GLFW/glfw3.h"

class Client
{
public:

	Client(UINT16 Port);
	~Client();

	void Update();

private:
	bool Connect (UINT16 Port);

	SOCKET m_socket;
	UINT64 m_playerID;
	addrinfo* result = 0, hints;
};

#endif // CLIENT_H