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
	virtual ~Server();

	bool Start(unsigned short port);
	void Listen();
	void ListenASync();
	void HandleClients();

	std::vector<SOCKET> clientConnections;

	std::vector<char> Receive(SOCKET ClientSocket);
	std::string ReceiveMessage(SOCKET ClientSocket);

	void Send(SOCKET clientSocket, std::string message);
	void Send(std::string message);

	void Send(std::vector<char> message);
	void Send(SOCKET clientSocket, std::vector<char> message);
	void SendExcept(SOCKET socket, std::vector<char> message); 

	bool Disconnect();

private:
	SOCKET listeningSocket;
	std::thread listeningThread;
};

#endif // SERVER
