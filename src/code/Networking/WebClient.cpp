
#include "Networking/WebClient.h"

#include <iostream>
#include <iterator>
#include <list>
#include <vector>

#include <WS2tcpip.h>


WebClient::WebClient(std::string url)
: m_socket( 0 )
{
	if (StartWinSock() == 1)
	{
		
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	//sockaddr_in6 serverAddress;
	char* ipString;

	hostent* h = gethostbyname(url.c_str());
	if (h == nullptr)
	{
		std::cout << "Host not found, h is null" << std::endl;
	}
	else
	{
		ipString = inet_ntoa(*((struct in_addr*)h->h_addr_list[0]));
		getaddrinfo(ipString, "80", &hints, &result);
		m_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (m_socket)
		{
			std::cout << "Connected to " << std::endl;
			printf("socket created, ip to web server: %.*s", INET6_ADDRSTRLEN, ipString);
			std::cout << std::endl;
		}
	}
}

int StartWinSock()
{
	WSADATA wsaData;

	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	return 0;
}


WebClient::~WebClient()
{
	closesocket(m_socket);
}

bool WebClient::Connect()
{
	if (connect(m_socket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
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

void WebClient::GetHTTP(const std::string url, const std::string ext)
{
	const int bufferLen = 2048;
	char buffer[bufferLen];
	int length = -1;
	std::string get_http = "GET " + ext + " HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";

	send(m_socket, get_http.c_str(), strlen(get_http.c_str()), 0);

	length = recv(m_socket, buffer, bufferLen, 0);

	std::cout << "length: " << length << std::endl;
	if (length > 0)
	{
		printf("buffer: %s", buffer);
		printf("web buffer: %.*s", length, buffer);

		//split the char array in smaller parts
		std::vector<char*> toks = std::vector<char*>();
		char* tok = strtok(buffer, " ,");
		if(tok)
			toks.push_back(tok);
		while (tok != NULL)
		{
			tok = strtok(NULL, " ,");
			if(tok)
				toks.push_back(tok);
		}

		//for each (char* tok in toks)
		//{
		//	printf("%s\n", tok);
		//}

		printf("\n	In %s the time and date is: \n", toks[41]);
		printf("	%s\n\n", toks[33]);
	}
}