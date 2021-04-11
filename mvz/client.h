#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>

#include <iostream>
#include <string>

class Client
{
public:
	
	Client();
	virtual ~Client();

	bool Connect(char* host, unsigned short port);

	void Send(std::string message);
	std::string Receive();

	bool Disconnect();

private:
	unsigned int GetIP(char* host);

	SOCKET TCPSocket;
};

#endif //CLIENT_H
