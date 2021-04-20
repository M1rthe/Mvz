#include "server.h"

Server::Server()
{
	// Initialze winsock
	WORD version = MAKEWORD(1, 1);
	WSADATA wsaData;

	if (WSAStartup(version, &wsaData) != 0)
	{
		std::cout << "Can't Initialize winsock, #" << WSAGetLastError() << std::endl;
	}

	listeningSocket = INVALID_SOCKET;
}

Server::~Server()
{
	//Disconnect();
}

bool Server::Start(unsigned short port) {

	if (listeningSocket != INVALID_SOCKET)
	{
		closesocket(listeningSocket);
		listeningSocket = INVALID_SOCKET;
	}

	// Create listening socket
	listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listeningSocket == INVALID_SOCKET)
	{
		std::cout << "Failed to create listening socket" << std::endl;

		return false;
	}

	// Fill in hint structure
	struct addrinfo* result = NULL;
	struct addrinfo* ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	std::ostringstream oss;
	oss << port;

	// Resolve the local address and port to be used by the server
	if (getaddrinfo(NULL, oss.str().c_str(), &hints, &result) != 0)
	{
		std::cout << "Failed to get addr info, #" << WSAGetLastError() << std::endl;
		freeaddrinfo(result);

		return false;
	}

	// Bind socket
	if (bind(listeningSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
	{
		std::cout << "Failed to bind listening socket" << std::endl;
		freeaddrinfo(result);
		closesocket(listeningSocket);
		listeningSocket = INVALID_SOCKET;

		return false;
	}

	freeaddrinfo(result);

	// Listen
	if (listen(listeningSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cout << "Failed on listen, #" << WSAGetLastError() << std::endl;
		closesocket(listeningSocket);
		listeningSocket = INVALID_SOCKET;

		return false;
	}

	std::cout << std::endl;
	std::cout << "Create server" << std::endl;
	std::cout << "-------------------" << std::endl;

	return true;
}

void Server::Listen()
{
	while (true)
	{
		// FD
		FD_SET readSet;
		FD_ZERO(&readSet);
		FD_SET(listeningSocket, &readSet);

		// TimeOut 
		timeval timeOut;
		timeOut.tv_usec = 0;

		// Select
		int totalBytes = select(0, &readSet, nullptr, nullptr, &timeOut);
		if (totalBytes == SOCKET_ERROR)
		{
			std::cout << "SERVER listen: Failed on select, #" << WSAGetLastError() << std::endl;

			return;
		}

		// Accept
		if (totalBytes > 0)
		{
			SOCKET clientSocket = accept(listeningSocket, nullptr, nullptr);;
			if (clientSocket == INVALID_SOCKET)
			{
				std::cout << "Failed on accept, #" << WSAGetLastError() << std::endl;
			}

			std::cout << "Client " << clientSocket << " joined server" << std::endl;
			clientConnections.push_back(clientSocket);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Server::ListenASync()
{
	listeningThread = std::thread(&Server::Listen, this);
	listeningThread.detach();
}

void Server::HandleClients()
{
	for (size_t i = 0; i < clientConnections.size(); i++)
	{
		std::string message = ReceiveMessage(clientConnections[i]);
		if (message != "")
		{
			//Send(clientConnections[i], "server echo: "+message);
			Send(clientConnections[i], message);
		}
	}
}

std::vector<char> Server::Receive(SOCKET clientSocket)
{
	std::vector<char> data;
	char recvbuf[512] = { NULL };

	// FD
	FD_SET readSet;
	FD_ZERO(&readSet);
	FD_SET(clientSocket, &readSet);

	// TimeOut 
	timeval timeOut;
	timeOut.tv_usec = 0;

	// Select
	int totalBytes = select(0, &readSet, nullptr, nullptr, &timeOut);

	if (totalBytes == SOCKET_ERROR)
	{
		std::cout << "Server receive: Failed on select, #" << WSAGetLastError() << std::endl;
	}
	if (totalBytes > 0)
	{
		totalBytes = recv(clientSocket, recvbuf, 512, 0);
		if (totalBytes > 0)
		{
			//message.append(&(recvbuf[0]), totalBytes);
			//recvbuf[0] = '\0';
		}
		else if (totalBytes == 0)
		{
			// Connection closed
			std::cout << "client " << clientSocket << " closed connection" << std::endl;

			clientConnections.erase(std::remove(clientConnections.begin(), clientConnections.end(), clientSocket), clientConnections.end());
		}
		else
		{
			std::cout << "Failed to receive message, totalBytes: "<< totalBytes<<", #" << WSAGetLastError() << std::endl;
		}
	}

	for (int i = 0; i < totalBytes; i++)
	{
		data.push_back(recvbuf[i]);
	}

	return data;
}

std::string Server::ReceiveMessage(SOCKET clientSocket)
{
	std::string message;

	// FD
	FD_SET readSet;
	FD_ZERO(&readSet);
	FD_SET(clientSocket, &readSet);

	// TimeOut 
	timeval timeOut;
	timeOut.tv_usec = 0;

	// Select
	int totalBytes = select(0, &readSet, nullptr, nullptr, &timeOut);

	if (totalBytes == SOCKET_ERROR)
	{
		std::cout << "Server receive: Failed on select, #" << WSAGetLastError() << std::endl;

		return "";
	}
	if (totalBytes > 0)
	{
		char recvbuf[512];

		totalBytes = recv(clientSocket, recvbuf, 512, 0);
		if (totalBytes > 0)
		{
			message.append(&(recvbuf[0]), totalBytes);
			recvbuf[0] = '\0';

			std::cout << message << std::endl;
		}
		else if (totalBytes == 0)
		{
			// Connection closed
			std::cout << "client " << clientSocket << " closed connection" << std::endl;

			clientConnections.erase(std::remove(clientConnections.begin(), clientConnections.end(), clientSocket), clientConnections.end());
		}
		else
		{
			std::cout << "Failed to receive message, totalBytes: " << totalBytes << ", #" << WSAGetLastError() << std::endl;
		}
	}

	return message;
}

void Server::Send(SOCKET clientSocket, std::string message)
{
	if (send(clientSocket, message.c_str(), message.size(), 0) == SOCKET_ERROR)
	{
		std::cout << "Failed to send message, #" << WSAGetLastError() << std::endl;

		return;
	}
}

void Server::Send(std::string message)
{
	for (size_t i = 0; i < clientConnections.size(); i++)
	{
		if (send(clientConnections[i], message.c_str(), message.size(), 0) == SOCKET_ERROR)
		{
			std::cout << "Failed to send message to " << clientConnections[i] << ", #" << WSAGetLastError() << std::endl;

			//return;
		}
		else {
			std::cout << "Send: " << message << std::endl;
		}
	}
}

void Server::Send(std::vector<char> data)
{
	for (size_t i = 0; i < clientConnections.size(); i++)
	{
		Send(clientConnections[i], data);
	}
}

void Server::Send(SOCKET clientSocket, std::vector<char> message)
{
	if (send(clientSocket, &message[0], message.size(), 0) == SOCKET_ERROR)
	{
		std::cout << "Failed to send message to " << clientSocket << ", #" << WSAGetLastError() << std::endl;

		//return;
	}
}

void Server::SendExcept(SOCKET socket, std::vector<char> message)
{
	for (size_t i = 0; i < clientConnections.size(); i++)
	{
		if (clientConnections[i] != socket) {
			Send(clientConnections[i], message);
		}
	}
}


bool Server::Disconnect()
{
	Send("host disconnected");

	if (listeningSocket != INVALID_SOCKET)
	{
		if (shutdown(listeningSocket, SD_RECEIVE) == SOCKET_ERROR)
		{
			std::cout << "Failed to shut down, #" << WSAGetLastError() << std::endl;
			closesocket(listeningSocket);
			listeningSocket = INVALID_SOCKET;

			return false;
		}

		closesocket(listeningSocket);
		listeningSocket = INVALID_SOCKET;

		return true;
	}

	std::cout << "socket was already closed" << std::endl;

	return true;
}