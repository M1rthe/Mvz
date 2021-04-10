#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <WS2tcpip.h>

#include <thread>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

class Server
{
public:
	
	Server();
	bool Start(unsigned short port);
	void Listen();
	void ListenASync();
	void HandleClients();

	std::vector<SOCKET> clientConnections;
	std::string Receive(SOCKET ClientSocket);
	void Send(SOCKET clientSocket, std::string message);
	void Send(std::string message);

private:
	SOCKET listeningSocket;
};

#endif // SERVER
