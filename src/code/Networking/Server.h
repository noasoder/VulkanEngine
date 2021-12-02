#ifndef SERVER_H
#define SERVER_H

#include <map>
#include <iterator>
#include <string>

#include "Networking/Networking.h"
#include "Types.h"
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
	#ifdef WINDOWS
		sockaddr address;
	#endif // WINDOWS
		int socket;
		PlayerInfo playerInfo;
	};

	Server(const uint16_t Port);
	~Server();

	void Update();


private:

	static void	ConnectThread(Server* pThis);
	void ReceiveFromClients();
	void Accept();

	std::map<int, Connection> m_connections;

	bool m_acceptThreadShouldRun;
	
	std::mutex* m_pConnectionsMutex;

	int m_socket;
#ifdef WINDOWS
	struct addrinfo* result = 0, hints;
#endif // WINDOWS
};

#endif // SERVER_H