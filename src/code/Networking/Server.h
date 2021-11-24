#ifndef SERVER_H
#define SERVER_H

#include <vector>

#include "Networking/Networking.h"
#include <thread>
#include <mutex>

class Server
{
public:

	struct Connection
	{
		sockaddr address;
		SOCKET socket;
	};

	Server(const UINT16 Port);
	~Server();

	void Update();

private:

	static void	ConnectThread(Server* pThis);
	void Accept();

	std::vector<Connection> m_connections;


	bool m_acceptThreadShouldRun;
	std::thread* m_pAcceptThread;
	
	std::mutex* m_pConnectionsMutex;


	SOCKET m_socket;
	struct addrinfo* result = 0, hints;

};

#endif // SERVER_H