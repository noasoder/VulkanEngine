
#ifndef CLIENT_H
#define CLIENT_H

#include "Types.h"

#include "Networking/Networking.h"
#include "GLFW/glfw3.h"

class Client
{
public:

	Client(UINT16 Port);
	~Client();

	void Update();

	bool m_isConnected = false;
	SOCKET m_socket;
private:
	void ReceiveFromServer();
	void SendToServer();
	bool Connect (UINT16 Port);

	UINT64 m_playerID;
};

#endif // CLIENT_H