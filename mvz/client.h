#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#include <WS2tcpip.h>

#include <sstream>
#include <iostream>
#include <string>

#include "button.h"

class Client
{
public:
	
	Client();
	virtual ~Client();

	bool Connect(char* host, unsigned short port);
	bool Connect(unsigned short port);

	void Send(std::string message);
	void Send(std::vector<char> message);

	//void Send(char* bytes); 
	std::string ReceiveMessage();
	std::vector<char> Receive();

	bool Disconnect();

private:
	unsigned int GetIP(char* host);

	SOCKET TCPSocket;
};

#endif //CLIENT_H
