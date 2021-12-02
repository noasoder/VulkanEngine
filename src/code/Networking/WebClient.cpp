
#include "Networking/WebClient.h"

#include <Networking/Networking.h>

#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <thread>

#define PRINT_WHOLE_BUFFER false

#ifdef WINDOWS
bool Connect(int socket, addrinfo* result)
{
	if (connect(socket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
	{
		std::cout << "SOCKET_ERROR" << std::endl;
	}
	else
	{
		std::cout << "connected to web" << std::endl;
		return true;
	}

	return false;
}
#endif // WINDOWS

void SendAndRecv(const std::string url, const std::string ext, int socket)
{
#ifdef WINDOWS
	const int bufferLen = 2048;
	char buffer[bufferLen];
	int length = -1;
	std::string get_http = "GET " + ext + " HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";

	//sent a get request to the server
	send(socket, get_http.c_str(), (int)strlen(get_http.c_str()), 0);
	//wait for a response
	length = recv(socket, buffer, bufferLen, 0);

	//printf("length: %i\n", length);
	if (length > 0)
	{
		if(PRINT_WHOLE_BUFFER)
			printf("buffer: \n %.*s", length, buffer);

		//split the char array in smaller parts
		std::vector<char*> toks = std::vector<char*>();
		char* tok = strtok(buffer, " ,");
		if (tok)
			toks.push_back(tok);
		while (tok != NULL)
		{
			tok = strtok(NULL, " ,");
			if (tok)
				toks.push_back(tok);
		}	WSAClea
		//	printf("%s\n", tok);
		//}

		//print the desired info
		printf("\n\n	In your %s the date and time is: \n", toks[41]);
		printf("		%s\n\n", toks[33]);
	}
#endif // WINDOWS
}

WebClient::WebClient(std::string url, std::string ext)
{
	m_socket = 0;
#ifdef WINDOWS
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	hostent* h = gethostbyname(url.c_str());
	if (h == nullptr)
	{
		printf("Host not found, h is null\n");
	}
	else
	{
		char ipString[INET6_ADDRSTRLEN];
		inet_ntop(AF_INET, (struct in_addr*)h->h_addr_list[0], ipString, sizeof(ipString));
		getaddrinfo(ipString, "80", &hints, &result);

		m_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (m_socket)
		{
			printf("socket created, ip to http server: %.*s\n", (int)sizeof(ipString), ipString);
		}

		m_connected = Connect(m_socket, result);

		if (m_connected)
			GetHTTP(url, ext);
	}
#endif // WINDOWS
}

WebClient::~WebClient()
{
#ifdef WINDOWS
	closesocket(m_socket);
#endif // WINDOWS
}

void WebClient::GetHTTP(const std::string url, const std::string ext)
{
	std::thread(SendAndRecv, url, ext, m_socket).detach();
}