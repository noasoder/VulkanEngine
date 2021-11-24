#ifndef SERVER_H
#define SERVER_H

#include <vector>

#include "Networking/Networking.h"

class Server
{
public:

	struct SConnection
	{
		sockaddr_in6	Address;
		tgSize			Socket;

	};	// SConnection

	typedef std::vector< SConnection >	ConnectionVector;

	explicit Server	( const tgUInt16 Port );
	        Server	( void );

	void	Update	( void );

private:

	static void	ThreadEntry	( tgCThread* pThread );

	void	Accept	( void );

	ConnectionVector	m_Connections;

	tgCThread*			m_pAcceptThread;
	tgCMutex*			m_pConnectionsMutex;

	tgSize				m_Socket;

	tgBool				m_ThreadShouldRun;

	struct addrinfo*	result = NULL, 
						hints;

}

#endif // SERVER_H