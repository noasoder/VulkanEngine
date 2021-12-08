#ifndef SERVER_H
#define SERVER_H

#include <map>
#include <iterator>
#include <string>

#include "Networking/Networking.h"
#include "Networking/UDPSocket.h"
#include "Types.h"

class UDPSocket;

class Server
{
public:

	struct PlayerInfo
	{
		std::string name;
		Vec3 position = Vec3();
		Vec3 rotation = Vec3();
	};

	struct Connection
	{
	#ifdef WINDOWS
		sockaddr_in address;
	#endif // WINDOWS
		PlayerInfo playerInfo;
	};

	Server(const uint16_t Port);
	~Server();

	void Update();

	UDPSocket* m_socket;
private:
	void Receive();
	void Decode(std::string buff, Connection&);

	std::map<std::string, Connection> m_connections;

};

#endif // SERVER_H