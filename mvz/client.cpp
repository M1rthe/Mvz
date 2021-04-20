#include "client.h"

Client::Client()
{
	// Initialze winsock
	WORD version = MAKEWORD(1, 1);
	WSADATA wsaData;

	if (WSAStartup(version, &wsaData) != 0)
	{
		std::cout << "Can't Initialize winsock, #" << WSAGetLastError() << std::endl;
	}

	TCPSocket = INVALID_SOCKET;
}

Client::~Client() 
{
	std::cout << "DESTRUCTOR client" << std::endl;
	//Disconnect();
}

bool Client::Connect(char* host, unsigned short port)
{
	if (TCPSocket != INVALID_SOCKET) 
	{
		closesocket(TCPSocket);
		TCPSocket = INVALID_SOCKET;
	}

	unsigned int remoteAddress = GetIP(host);
	if (remoteAddress == INADDR_NONE)
	{
		return false;
	}

	// Create TCPSocket
	TCPSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (TCPSocket == INVALID_SOCKET)
	{
		std::cout << "Failed to create socket, #" << WSAGetLastError() << std::endl;

		return false;
	}

	sockaddr_in remote;
	remote.sin_family = AF_INET;
	remote.sin_addr.s_addr = remoteAddress;
	remote.sin_port = htons(port);

	//Connect
	if (connect(TCPSocket, (sockaddr*)&remote, sizeof(remote)) == SOCKET_ERROR)
	{
		std::cout << "Failed to connect, #" << WSAGetLastError() << std::endl;

		closesocket(TCPSocket);
		TCPSocket = INVALID_SOCKET;

		return false;
	}

	//Set non-blocking mode
	u_long iMode = 1;
	if (ioctlsocket(TCPSocket, FIONBIO, &iMode) != NO_ERROR)
	{
		std::cout << "Failed to set non-blocking mode, #" << WSAGetLastError() << std::endl;
	}

	//setsockopt(TCPSocket, IPPROTO_TCP, TCP_NODELAY, (char*)'1', sizeof(unsigned int));

	std::cout << std::endl;
	std::cout << "Succesfully connected" << std::endl;
	std::cout << "-------------------" << std::endl;

	return true;
}

bool Client::Connect(unsigned short port)
{
	// Close Socket
	if (TCPSocket != INVALID_SOCKET)
	{
		closesocket(TCPSocket);
		TCPSocket = INVALID_SOCKET;
	}

	// Initialze winsock
	WORD version = MAKEWORD(1, 1);
	WSADATA wsaData;

	// Startup
	int iResult = WSAStartup(version, &wsaData);
	if (iResult != 0)
	{
		std::cout << "Can't Initialize winsock, #" << WSAGetLastError() << std::endl;

		return false;
	}

	// Fill in hint structure
	struct addrinfo* result = NULL;
	struct addrinfo* ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	std::ostringstream oss;
	oss << port;

	iResult = getaddrinfo(NULL, oss.str().c_str(), &hints, &result);

	if (iResult != 0) {
		std::cout << "getaddrinfo failed with error: " << iResult << std::endl;

		return false;
	}

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		//Socket
		TCPSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (TCPSocket == INVALID_SOCKET)
		{
			std::cout << "Failed to create socket, #" << WSAGetLastError() << std::endl;
			WSACleanup();

			return false;
		}

		//Connect
		iResult = connect(TCPSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			closesocket(TCPSocket);
			TCPSocket = INVALID_SOCKET;

			continue;
		}

		break;
	}

	freeaddrinfo(result);

	if (TCPSocket == INVALID_SOCKET)
	{
		std::cout << "Unable to connect to server" << std::endl;

		return false;
	}

	std::cout << std::endl;
	std::cout << "Succesfully connected" << std::endl;
	std::cout << "-------------------" << std::endl;

	return true;
}

void Client::Send(std::string message)
{
	if (send(TCPSocket, message.c_str(), message.size(), 0) == SOCKET_ERROR)
	{
		std::cout << "Failed to send: " << message << ", #" << WSAGetLastError() << std::endl;
		return;
	}
	else {
		std::cout << "Send: " << message << std::endl;
	}
}

void Client::Send(std::vector<char> data)
{
	if (send(TCPSocket, &data[0], data.size(), 0) == SOCKET_ERROR)
	{
		std::cout << "Failed to send, #" << WSAGetLastError() << std::endl;
		return;
	} 
}

std::vector<char> Client::Receive()
{
	char recvbuf[512] = { NULL }; 
	std::vector<char> data;

	// FD
	FD_SET readSet;
	FD_ZERO(&readSet);
	FD_SET(TCPSocket, &readSet);

	// TimeOut 
	timeval timeOut;
	timeOut.tv_usec = 0;

	// Select
	int totalBytes = select(0, &readSet, nullptr, nullptr, &timeOut);
	if (totalBytes == SOCKET_ERROR)
	{
		std::cout << "Failed on select, #" << WSAGetLastError() << std::endl;
	}

	if (totalBytes > 0)
	{
		totalBytes = recv(TCPSocket, recvbuf, 512, 0);
		if (totalBytes > 0)
		{
			//message.append(&(recvbuf[0]), totalBytes);
			//data[0] = '\0';
		}
		else if (totalBytes == 0)
		{
			// Connection closed
			std::cout << "server disconnected" << std::endl;
		}
		else
		{
			std::cout << "Failed to receive message, #" << WSAGetLastError() << std::endl;
		}
	}

	for (int i = 0; i < totalBytes; i++)
	{
		data.push_back(recvbuf[i]);
	}

	return data;
}

std::string Client::ReceiveMessage()
{
	std::string message;

	// FD
	FD_SET readSet;
	FD_ZERO(&readSet);
	FD_SET(TCPSocket, &readSet);

	// TimeOut 
	timeval timeOut;
	timeOut.tv_usec = 0;

	// Select
	int totalBytes = select(0, &readSet, nullptr, nullptr, &timeOut);
	if (totalBytes == SOCKET_ERROR)
	{
		std::cout << "Failed on select, #" << WSAGetLastError() << std::endl;

		return "";
	}

	if (totalBytes > 0)
	{
		char recvbuf[512];

		totalBytes = recv(TCPSocket, recvbuf, 512, 0);
		if (totalBytes > 0)
		{
			message.append(&(recvbuf[0]), totalBytes);
			recvbuf[0] = '\0';
		}
		else if (totalBytes == 0)
		{
			// Connection closed
			std::cout << "server disconnected" << std::endl;
		}
		else
		{
			std::cout << "Failed to receive message, #" << WSAGetLastError() << std::endl;
		}
	}

	return message;
}

bool Client::Disconnect()
{
	if (TCPSocket != INVALID_SOCKET)
	{
		if (shutdown(TCPSocket, SD_SEND) == SOCKET_ERROR)
		{
			std::cout << "Client failed to shut down, #" << WSAGetLastError() << std::endl;
			closesocket(TCPSocket);
			TCPSocket = INVALID_SOCKET;

			return false;
		}

		closesocket(TCPSocket);
		TCPSocket = INVALID_SOCKET;

		return true;
	}

	std::cout << "Disconnect: socket is already closed" << std::endl;

	return true;
}

unsigned int Client::GetIP(char* host)
{
	unsigned int remoteAddress = inet_addr(host);
	if (remoteAddress == INADDR_NONE)
	{
		// Host isn't a dotted IP, so resolve it through DNS
		hostent* hostEnt = gethostbyname(host);
		if (hostEnt == 0)
		{
			return INADDR_NONE;
		}

		remoteAddress = *(u_long*)hostEnt->h_addr_list[0];
	}

	return remoteAddress;
}