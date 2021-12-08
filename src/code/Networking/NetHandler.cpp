
#include "Networking/NetHandler.h"

#include "Networking/Networking.h"
#include "Networking/WebClient.h"
#include "Networking/Server.h"
#include "Networking/Client.h"
#include "Managers/InputManager.h"

#include <stdio.h>

#define PORT 69


int StartWinSock()
{
	#ifdef WINDOWS
	WSADATA wsaData;

	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	#endif // WINDOWS
	return 0;
}

NetHandler::NetHandler()
{
	StartWinSock();

	//const std::string url = "www.noasoderlund.com";
	//const std::string ext = "/projects/index.html";
	const std::string url = "www.worldtimeapi.org";
	const std::string ext = "/api/ip";
	//const std::string ext = "/api/timezone/Europe/Stockholm";
	//const std::string ext = "/api/timezone/Africa/Johannesburg";
	//const std::string ext = "/api/timezone/Asia/Tokyo";

	m_pWebClient = new WebClient(url, ext);


}

NetHandler::~NetHandler()
{
	if (m_pWebClient)
		delete m_pWebClient;

	if (m_pClient)
		delete m_pClient;
	if (m_pServer)
		delete m_pServer;
	#ifdef WINDOWS
	WSACleanup();
	#endif // WINDOWS
}


void NetHandler::Update()
{
	if (!m_pServer && InputManager::GetKeyDown(GLFW_KEY_M))
	{
		m_pServer = new Server(PORT);
	}
	if (!m_pClient && InputManager::GetKeyDown(GLFW_KEY_C))
	{
		m_pClient = new Client(PORT);
	}
	if (m_pClient && InputManager::GetKeyDown(GLFW_KEY_V))
	{
		delete m_pClient;
		m_pClient = nullptr;
	}
	if (m_pServer && InputManager::GetKeyDown(GLFW_KEY_B))
	{
		delete m_pServer;
		m_pServer = nullptr;
	}

	if (m_pServer)
		m_pServer->Update();
	if (m_pClient)
		m_pClient->Update();
}