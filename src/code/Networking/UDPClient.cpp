
#include "Networking/UDPClient.h"

#include "Networking/Networking.h"

#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <string>
#include <thread>

#include "Managers/InputManager.h"
#include "Networking/UDPSocket.h"

struct	PlayerState
{
	Vec3 Position = Vec3(0, 0, 0);
	Vec3 Rotation = Vec3(0, 0, 0);
};

UDPClient::UDPClient(uint16_t Port)
{
	m_socket = new UDPSocket();
	m_port = Port;
}

UDPClient::~UDPClient()
{
	delete m_socket;
}

void UDPClient::Update()
{
	if (InputManager::GetKeyDown(GLFW_KEY_X))
	{
		std::string data = "hello world";
		m_socket->SendTo("127.0.0.1", m_port, data.c_str(), data.size());
	}

	Receive();
}

void UDPClient::Receive()
{
	char buffer[100];

	sockaddr_in add;
	if (m_socket->RecvFrom(add, buffer, 100) > 0)
	{
		printf("CLIENT: recv: %s\n", buffer);
	}
}