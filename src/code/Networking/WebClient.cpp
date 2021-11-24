
#include "Networking/WebClient.h"

#include <Networking/Networking.h>

#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <thread>

bool Connect(SOCKET socket, addrinfo* result)
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

void SendAndRecv(const std::string url, const std::string ext, SOCKET socket)
{
	const int bufferLen = 2048;
	char buffer[bufferLen];
	int length = -1;
	std::string get_http = "GET " + ext + " HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";

	//sent a get request to the server
	send(socket, get_http.c_str(), (int)strlen(get_http.c_str()), 0);
	//wait for a response
	length = recv(socket, buffer, bufferLen, 0);

	std::cout << "length: " << length << std::endl;
	if (length > 0)
	{
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
		}

		//for each (char* tok in toks)
		//{
		//	printf("%s\n", tok);
		//}

		//print the desired info
		printf("\n\n	In %s the time and date is: \n", toks[41]);
		printf("	%s\n\n", toks[33]);
	}
}

WebClient::WebClient(std::string url, std::string ext)
{
	m_socket = 0;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	hostent* h = gethostbyname(url.c_str());
	if (h == nullptr)
	{
		std::cout << "Host not found, h is null" << std::endl;
	}
	else
	{
		char ipString[INET6_ADDRSTRLEN];
		inet_ntop(AF_INET, (struct in_addr*)h->h_addr_list[0], ipString, sizeof(ipString));
		getaddrinfo(ipString, "80", &hints, &result);

		m_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (m_socket)
		{
			printf("socket created, ip to http server: %.*s", sizeof(ipString), ipString);
			std::cout << std::endl;
		}

		m_connected = Connect(m_socket, result);

		if (m_connected)
			GetHTTP(url, ext);
	}
}

WebClient::~WebClient()
{
	closesocket(m_socket);
}

void WebClient::GetHTTP(const std::string url, const std::string ext)
{
	std::thread(SendAndRecv, url, ext, m_socket).detach();
}