
#ifndef CLIENT_H
#define CLIENT_H

#include "Types.h"

#include "Networking/Networking.h"
#include "GLFW/glfw3.h"
#include <thread>
#include <future>

#define SERVER_IP "192.168.56.1"

class UDPSocket;

class Client
{
public:

	Client(uint16_t Port);
	~Client();

	void Update();

	bool m_isConnected = false;
	UDPSocket* m_socket;
	std::string m_playerName = "UWU";

private:
	void Receive();

	uint16_t m_port;

	std::thread connectThread;
	std::promise<void> stopThread;
};

#endif // CLIENT_H