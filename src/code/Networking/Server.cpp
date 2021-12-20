
#include "Networking/Server.h"

#include <iostream>
#include <string>
#include <vector>

#include "Managers/InputManager.h"
#include "Networking/UDPSocket.h"

Server::Server( const uint16_t Port )
{
	m_socket = new UDPSocket();
	m_socket->Bind(Port);

	char ac[80];
	gethostname(ac, sizeof(ac));
	struct hostent* phe = gethostbyname(ac);
	for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
		struct in_addr addr;
		memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
		std::cout << "Address " << i << ": " << inet_ntoa(addr) << std::endl;
	}
}

Server::~Server()
{
	m_connections.clear();

	delete m_socket;
}

void Server::Update( void )
{
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
}

void Server::Receive()
{
	std::vector<int> keysToRemove;

	char buffer[128];
	sockaddr_in add;

	int result = m_socket->RecvFrom(add, buffer, sizeof(buffer));
	if (result > 0)
	{
		Connection newCon = Connection();
		newCon.address = add;
		Decode(buffer, newCon);
	}
	else if (result == -1)
	{
		m_connections.erase(inet_ntoa(add.sin_addr));
	}
}

void Server::Decode(std::string buff, Connection& con)
{
	if (buff.length() < 4)
		return;

	std::string cmd = buff.substr(0, 4);
	if (cmd == "ncon")
	{
		//new connection
		std::string name = buff.substr(4);
		con.playerInfo.name = name;
		int beforeInsert = m_connections.size();
		//try to add the connection to the connections
		m_connections.insert(std::make_pair(inet_ntoa(con.address.sin_addr) + std::string(" " + name), con));

		if (beforeInsert != m_connections.size())
		{
			printf("SERVER: new conn\n");
			m_socket->SendTo(con.address, std::string("acnc" + name).c_str(), 4);
		}
	}
	else if (cmd == "dscn")
	{
		//disconnect
		std::string ipAndName = inet_ntoa(con.address.sin_addr) + std::string(" " + buff.substr(4));
		m_connections.erase(ipAndName);

		printf("SERVER: %s disconnected\n", ipAndName.c_str());
	}
	else
	{
		printf("SERVER: recv: %s\n", buff.c_str());
	}
}
