
#include "Networking/Client.h"

#include "Networking/Networking.h"

#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <string>
#include <thread>

#include "Managers/InputManager.h"

struct	PlayerState
{
	Vec3 Position = Vec3(0, 0, 0);
	Vec3 Rotation = Vec3(0, 0, 0);
};

void ConnectToServer(Client* pThis, UINT16 Port)
{
	addrinfo* result = 0, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	//sockaddr_in6 serverAddress;
	char ipString[INET6_ADDRSTRLEN];
	inet_ntop(AF_INET6, &in6addr_loopback, ipString, INET6_ADDRSTRLEN);

	//char* ipString = "";

	getaddrinfo(ipString, std::to_string(Port).c_str(), &hints, &result);

	pThis->m_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	printf("CLIENT: socket created, ip to remote server: %.*s\n", INET_ADDRSTRLEN, ipString);
	while (!pThis->m_isConnected)
	{
		if (connect(pThis->m_socket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
			printf("CLIENT: Looking for server\n");
			Sleep(500);
		}
		else {
			printf("CLIENT: connected to server\n");
			pThis->m_isConnected = true;
		}
	}
}

Client::Client(UINT16 Port)
{
	m_socket = 0;
	m_playerID = 0;

	std::thread(ConnectToServer, this, Port).detach();
}

Client::~Client()
{
	if(m_socket)
		closesocket(m_socket);
}

bool Client::Connect(UINT16 Port)
{

	return false;
}


void Client::Update()
{
	ReceiveFromServer();
	SendToServer();
}

void Client::ReceiveFromServer()
{
	if (!m_socket)
		return;

	FD_SET readSet;
	FD_ZERO(&readSet);
	timeval timeout{ 0, 0 };

	//Add socket to the read set
	FD_SET(m_socket, &readSet);

	if (select((int)m_socket, &readSet, NULL, NULL, &timeout) == 1)
	{
		char recvBuffer[64];
		int recvLen = recv(m_socket, recvBuffer, 64, 0);
		if (recvLen == 0)
		{
			printf("CLIENT: closed recv: %.*s\n", recvLen, recvBuffer);
		}
		else
		{
			printf("CLIENT: recv: %.*s\n", recvLen, recvBuffer);
		}
	}
}

void Client::SendToServer()
{
	if (InputManager::GetKeyDown(GLFW_KEY_X))
	{
		std::string sendText = "Hello";
		send(m_socket, sendText.c_str(), (int)sendText.size(), 0);
	}
}

//FD_SET readfds;

	//FD_ZERO(&readfds);

	//const timeval timeout{ 0, 0 };

	////Add socket to the read array
	//FD_SET((SOCKET)m_socket, &readfds);

	//int result = select(0, &readfds, NULL, NULL, &timeout);

	//if (result == -1)
	//{
	//	std::cout << "select exited with result[-1]: %d\n" << WSAGetLastError() << std::endl;
	//}
	//else if (result == 0)
	//{
	//	//std::cout << "select exited with result: " << result << std::endl;
	//}
	//else
	//{
	//	//std::cout << "result: " << result;
	//	for (int i = 0; i < result; i++)
	//	{
	//		if (FD_ISSET((SOCKET)m_socket, &readfds))
	//		{
	//			const int headerLn = 8;
	//			const int bufferLn = 2048;
	//			//const int bufferLn = sizeof(SMessageHeader) + sizeof(SPlayerState);

	//			char header[headerLn];

	//			int recvLen = recv(m_socket, header, headerLn, 0);
	//			
	//			if (recvLen > 0)
	//			{
	//				std::string str = {header[0], header[1], header[2], header[3]};
	//				//std::cout << str;

	//				memcpy(&recvLen, header + 4, 4);
	//				//printf(" recvLen: %i", recvLen);

	//				if (str == "ackn")
	//				{
	//					char buffer[16];
	//					recvLen = recv(m_socket, buffer, recvLen, 0);

	//					memcpy(&m_playerID, buffer, recvLen);

	//					printf("My ID[%i]", m_playerID);
	//					printf("\n");
	//				}
	//				else if (str == "eror")
	//				{
	//					char buffer[512];
	//					recvLen = recv(m_socket, buffer, recvLen, 0);

	//					printf("Error: %s", buffer);
	//					printf("\n");
	//				}
	//				else if (str == "plst")
	//				{
	//					char buffer[512];
	//					recvLen = recv(m_socket, buffer, recvLen, 0);
	//				
	//					int offset = 0;
	//					//printf(" off: %i", offset);

	//					PlayerState playerState = PlayerState();
	//					UINT64 id;

	//					std::memcpy(&id, buffer + offset, sizeof(UINT64));
	//					offset += sizeof(UINT64);

	//					memcpy(&playerState.Position, buffer + offset, sizeof(Vec3));
	//					offset += sizeof(Vec3);

	//					memcpy(&playerState.Rotation, buffer + offset, sizeof(Vec3));
	//					offset += sizeof(Vec3);

	//					memcpy(&playerState.Animation, buffer + offset, sizeof(UINT8));
	//					offset += sizeof(UINT8);

	//					//CGameStates::GetInstance().GetStateGame()->SetPlayerState(id, playerState);
	//					//printf("\n");
	//				}
	//				else if (str == "disc")
	//				{
	//					UINT64 id;
	//					char buffer[16];
	//					recvLen = recv(m_socket, buffer, recvLen, 0);

	//					memcpy(&id, buffer, recvLen);

	//					//CGameStates::GetInstance().GetStateGame()->RemovePlayer(id);
	//					//printf("player[%s] disconnected", buffer);
	//					printf("player[%i] disconnected", id);
	//					printf("\n");
	//				}
	//			}
	//		}
	//	}
	//}

//void Client::SendPlayerState(const PlayerState& rState)
//{
//	const int plSize = sizeof(UINT64) + sizeof(Vec3) * 2 + sizeof(UINT8);
//	const int headerSize = 8;
//
//	char plst[4] = {'p', 'l', 's', 't'};
//
//	char buffer[headerSize + plSize];
//	int offset = 0;
//
//	memcpy(&buffer, &plst, sizeof(plst));
//	offset += sizeof(plst);
//
//	memcpy(&buffer[offset], &plSize, sizeof(plSize));
//	offset += sizeof(plSize);
//
//	memcpy(&buffer[offset], &m_playerID, sizeof(UINT64));
//	offset += sizeof(UINT64);
//
//	memcpy(&buffer[offset], &rState.Position, sizeof(Vec3));
//	offset += sizeof(Vec3);
//
//	memcpy(&buffer[offset], &rState.Rotation, sizeof(Vec3));
//	offset += sizeof(Vec3);
//
//	memcpy(&buffer[offset], &rState.Animation, sizeof(UINT8));
//	offset += sizeof(UINT8);
//
//	send(m_socket, buffer, headerSize + plSize, 0);
//}