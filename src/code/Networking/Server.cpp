
#include "Networking/Server.h"

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>

#include "Managers/InputManager.h"

Server::Server( const UINT16 Port )
: m_connections()
, m_pConnectionsMutex( 0 )
, m_socket( 0 )
, m_acceptThreadShouldRun( true )
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	char ipString[INET6_ADDRSTRLEN];

	inet_ntop(AF_INET6, &in6addr_loopback, ipString, INET6_ADDRSTRLEN);
	printf("SERVER: ipv6: %.*s\n", INET6_ADDRSTRLEN, ipString);

	int iResult = getaddrinfo(ipString, std::to_string((int)Port).c_str(), &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
	}

	m_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (m_socket == INVALID_SOCKET) {
		printf("socket failed with error: %d\n", WSAGetLastError());
	}

	bind(m_socket, result->ai_addr, (int)result->ai_addrlen);

	listen(m_socket, SOMAXCONN);

	m_pConnectionsMutex	= new std::mutex();

	m_acceptThreadShouldRun = true;
	std::thread(ConnectThread, this).detach();
}

Server::~Server()
{
	m_acceptThreadShouldRun = false;

	if (m_pConnectionsMutex)
	{
		delete m_pConnectionsMutex;
	}

	m_connections.clear();

	closesocket(m_socket);
}

void Server::Update( void )
{
	if (InputManager::GetKeyDown(GLFW_KEY_N))
	{
		std::map<int, Connection>::iterator conn = m_connections.begin();
		while (conn != m_connections.end())
		{
			std::string message = "To allll";
			send(conn->second.socket, message.c_str(), (int)message.length(), 0);
			conn++;
		}
	}

	m_pConnectionsMutex->lock();
	ReceiveFromClients();
	m_pConnectionsMutex->unlock();
}

void Server::ReceiveFromClients()
{
	std::vector<int> keysToRemove;
	std::map<int, Connection>::iterator conn = m_connections.begin();
	while (conn != m_connections.end())
	{
		FD_SET readSet;

		FD_ZERO(&readSet);

		timeval timeout{ 0, 0 };

		//Add socket to the read set
		FD_SET(conn->second.socket, &readSet);

		int result = select((int)conn->second.socket, &readSet, NULL, NULL, &timeout);

		if (result == -1)
		{
			printf("select exited with result: %d\n", WSAGetLastError());
		}
		else if (result == 0)
		{
			//std::cout << "select exited with result: " << result << std::endl;
		}
		else
		{
			if (FD_ISSET((SOCKET)conn->second.socket, &readSet))
			{
				const int recvLength = 512;
				char buffer[recvLength] = { 'T', 'E', 'S', 'T' };
				int length = recv(conn->second.socket, buffer, recvLength, 0);
				if (length > 0)
				{
					printf("SERVER: recv: %.*s\n", length, buffer);
				}
				else
				{
					printf("SERVER: connection to client closed");
					keysToRemove.push_back(conn->first);
				}
			}
		}

		conn++;
	}

	//Remove connections that where disconnected
	for (int key : keysToRemove)
	{
		m_connections.erase(key);
	}
}

void Server::ConnectThread(Server* pThis)
{
	while(pThis && pThis->m_acceptThreadShouldRun)
	{
		pThis->Accept();
		Sleep(250);
	}
}

void Server::Accept()
{	
	if (!m_socket || !m_pConnectionsMutex)
		return;

	FD_SET readSet;
	FD_ZERO(&readSet);

	FD_SET(m_socket, &readSet);
	timeval timeout{ 0, 0 };

	if (select(0, &readSet, NULL, NULL, &timeout) == 1)
	{
		Connection newCon = Connection();
		newCon.id = m_connections.size();
		newCon.socket = accept(m_socket, &newCon.address, NULL);
		if (newCon.socket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
		}
		else
		{
			printf("SERVER: client ip: %.*s\n", (int)sizeof(newCon.address.sa_data), newCon.address.sa_data);

			m_pConnectionsMutex->lock();
			m_connections.insert(std::make_pair(newCon.socket, newCon));
			m_pConnectionsMutex->unlock();
		}
	}
}