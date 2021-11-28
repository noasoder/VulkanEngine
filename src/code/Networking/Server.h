#ifndef SERVER_H
#define SERVER_H

#include <map>
#include <iterator>
#include <string>

#include "Networking/Networking.h"
#include <thread>
#include <mutex>

class Server
{
public:

	struct PlayerInfo
	{
		std::string name;
		Vec3 position;
		Vec3 rotation;
	};
	struct Connection
	{
		sockaddr address;
		int socket;
		PlayerInfo playerInfo;
	};

	Server(const UINT16 Port);
	~Server();

	void Update();


private:

	static void	ConnectThread(Server* pThis);
	void ReceiveFromClients();
	void Accept();

	std::map<int, Connection> m_connections;

	bool m_acceptThreadShouldRun;
	
	std::mutex* m_pConnectionsMutex;


	SOCKET m_socket;
	struct addrinfo* result = 0, hints;
};

#endif // SERVER_H