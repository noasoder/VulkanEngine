#pragma once

#include <string>

class WebClient
{
public:

	WebClient(std::string url);
	~WebClient();

	bool	Connect();
	void	GetHTTP(const std::string url, const std::string ext);

private:


};