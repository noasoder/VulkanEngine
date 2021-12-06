
#include "Networking/UDPServer.h"

#include <iostream>
#include <string>
#include <vector>

#include "Managers/InputManager.h"
#include "Networking/UDPSocket.h"

UDPServer::UDPServer( const uint16_t Port )
{
	m_socket = new UDPSocket();
	m_socket->Bind(Port);
}

UDPServer::~UDPServer()
{
	m_connections.clear();

	delete m_socket;
}

void UDPServer::Update( void )
{
#ifdef WINDOWS
	if (InputManager::GetKeyDown(GLFW_KEY_N))
	{
		std::map<std::string, Connection>::iterator conn = m_connections.begin();
		while (conn != m_connections.end())
		{
			std::string message = "To allll";
			m_socket->SendTo(conn->second.address, message.c_str(), (int)message.length());
			conn++;
		}
	}

	Receive();
#endif // WINDOWS
}

void UDPServer::Receive()
{
#ifdef WINDOWS


	std::vector<int> keysToRemove;

	char buffer[100];
	sockaddr_in add;

	int result = m_socket->RecvFrom(add, buffer, sizeof(buffer));
	if (result > 0)
	{
		Connection newCon = Connection();
		newCon.address = add;
		m_connections.insert(std::make_pair(inet_ntoa(add.sin_addr), newCon));

		std::string input(buffer);
		m_socket->SendTo(add, input.c_str(), input.size());
	}
	else if (result == -1)
	{
		m_connections.erase(inet_ntoa(add.sin_addr));
	}


#endif // WINDOWS
}
