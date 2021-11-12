
#ifndef CLIENT_H
#define CLIENT_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#include "Utility/Types.h"

struct	PlayerState
{
	Vec3 Position;
	Vec3 Rotation;
	UINT8 Animation;
};

class Client
{
public:

	Client	(const UINT16 Port);
	~Client	( void );

	bool	Connect			( const UINT16 Port );
	void	Update			( void );
	void	SendPlayerState	( const PlayerState& rState );

private:

	SOCKET m_socket;

	UINT64 m_playerID;

	struct addrinfo*	result = 0, hints;
};

#endif // CLIENT_H