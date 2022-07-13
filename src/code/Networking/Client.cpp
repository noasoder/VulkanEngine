
#include "Networking/Client.h"

#include "Networking/Networking.h"

#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <string>
#include <thread>
#include <future>
#include <chrono>

#include "Managers/InputManager.h"
#include "Networking/UDPSocket.h"

struct	PlayerState
{
	Vec3 Position = Vec3(0, 0, 0);
	Vec3 Rotation = Vec3(0, 0, 0);
};

void ConnectToServer(std::future<void> futureObj, Client* pThis, uint16_t Port)
{
#ifdef WINDOWS
	bool conn = false;
	while (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
	{
		if (conn)
			break;

		printf("CLIENT: Trying to connect\n");

		std::string data = "ncon" + pThis->m_playerName;
		pThis->m_socket->SendTo(SERVER_IP, Port, data.c_str(), data.size());
		
		Sleep(500);

		const int buffLen = 128;
		char buffer[buffLen];
		sockaddr_in add;
		if (pThis->m_socket->RecvFrom(add, buffer, buffLen))
		{
			std::string buff = buffer;
			if (buff.substr(0, 4) == "acnc")
			{
				printf("CLIENT: connected to server\n");
				conn = true;
				pThis->m_isConnected = true;
			}
		}
	}
#endif
}

Client::Client(uint16_t Port)
{
#ifdef WINDOWS
	m_socket = new UDPSocket();
	m_port = Port;

	connectThread = std::thread(ConnectToServer, std::move(stopThread.get_future()), this, Port);
#endif
}

Client::~Client()
{
#ifdef WINDOWS
	stopThread.set_value();
	//Wait for thread
	connectThread.join();

	std::string data = "dscn" + m_playerName;
	m_socket->SendTo(SERVER_IP, m_port, data.c_str(), data.size());

	delete m_socket;
#endif
}

void Client::Update()
{
#ifdef WINDOWS
	if (!m_isConnected)
		return;

	if (InputManager::GetKeyDown(GLFW_KEY_X))
	{
		std::string data = "hello world";
		m_socket->SendTo(SERVER_IP, m_port, data.c_str(), data.size());
	}

	Receive();
#endif
}

void Client::Receive()
{
#ifdef WINDOWS
	const int buffLen = 128;
	char buffer[buffLen];
	sockaddr_in add;

	if (m_socket->RecvFrom(add, buffer, buffLen) > 0)
	{
		printf("CLIENT: recv: %s\n", buffer);
	}
#endif
}