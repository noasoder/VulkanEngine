
#ifndef CLIENT_H
#define CLIENT_H

#include "Types.h"

#include "Networking/Networking.h"
#include "GLFW/glfw3.h"

class Client
{
public:

	Client(uint16_t Port);
	~Client();

	void Update();

	bool m_isConnected = false;
	int m_socket;
private:
	void ReceiveFromServer();
	void SendToServer();
	bool Connect (uint16_t Port);

	uint64_t m_playerID;
};

#endif // CLIENT_H