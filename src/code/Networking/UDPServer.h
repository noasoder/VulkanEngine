#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <map>
#include <iterator>
#include <string>

#include "Networking/Networking.h"
#include "Networking/UDPSocket.h"
#include "Types.h"

class UDPSocket;

class UDPServer
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
		sockaddr_in address;
	#endif // WINDOWS
		PlayerInfo playerInfo;
	};

	UDPServer(const uint16_t Port);
	~UDPServer();

	void Update();

	UDPSocket* m_socket;
private:
	void Receive();

	std::map<std::string, Connection> m_connections;

};

#endif // UDP_SERVER_H