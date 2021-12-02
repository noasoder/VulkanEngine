
#ifndef NET_HANDLER_H
#define NET_HANDLER_H

#include "Networking/Networking.h"

class Client;
class Server;
class WebClient;

class NetHandler
{
public:

	NetHandler();
	~NetHandler();

	void Update();

private:
	Client* m_pClient = nullptr;
	Server* m_pServer = nullptr;
	WebClient* m_pWebClient;
};


#endif // NET_HANDLER_H