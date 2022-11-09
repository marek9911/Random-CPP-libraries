#include <algorithm>
#include "Server.h"

Server::Server(
	uint16_t port, 
	std::function<void(SOCKET clientSocket, const char* bufferPtr, int bytesReceived)> receiverHandlerLambda, 
	std::function<void(SOCKET clientSocket)> welcomeHandlerLambda, 
	std::function<void(SOCKET clientSocket)> disconnectHandlerLambda
) : port(port) {
	this->clients.receiveHandler = receiverHandlerLambda;
	this->clients.welcomeHandler = welcomeHandlerLambda;
	this->clients.disconnectHandler = disconnectHandlerLambda;
	this->RestartServer();
}

Server::~Server() {
	this->ShutdownServer();
}

void Server::RestartServer() {
	// Winsock init
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0) {
		status = SERVER_WINSOCK_ERROR;
		return;
	}

	// Create socket
	this->listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->listeningSocket == INVALID_SOCKET) {
		this->status = SERVER_SOCKET_ERROR;
		return;
	}

	// Bind IP and port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	::bind(this->listeningSocket, (sockaddr*)&hint, sizeof(hint));

	// Tell winsock to listen
	listen(this->listeningSocket, SOMAXCONN);

	// Wait for connection
	sockaddr_in client;
	int clientSize = sizeof(client);
	this->status = SERVER_OPEN;
	this->listener = new std::thread(&Server::Listen, this);
}

void Server::ShutdownServer() {
	this->status = SERVER_CLOSED;
	closesocket(this->listeningSocket);
	this->listener->join();
	delete this->listener;
	while (this->clients.sockets.size() != 0) {
		closesocket(this->clients.sockets[0]);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

int Server::GetStatus() {
	return this->status;
}

int Server::GetNumberOfClients() {
	return (int)this->clients.sockets.size();
}

std::string Server::GetIPbySocket(SOCKET clientSocket) {
	return this->clients.dict[clientSocket];
}

void Server::Send(SOCKET clientSocket, const char* bytes, int size) {
	send(clientSocket, bytes, size, 0);
}

void Server::KickClient(SOCKET clientSocket) {
	closesocket(clientSocket);
}

void Server::Listen() {
	SOCKET clientSocket;
	sockaddr_in client;
	int clientSize = sizeof(client);

	while (status == SERVER_OPEN) {
		SOCKET clientSocket = accept(this->listeningSocket, (sockaddr*)&client, &clientSize);
		if (clientSocket == INVALID_SOCKET) {
			break;
		}

		char clientIP[NI_MAXHOST];
		inet_ntop(AF_INET, &client.sin_addr, clientIP, NI_MAXHOST);
		this->clients.dict.insert(std::make_pair(clientSocket, clientIP));
		this->clients.sockets.push_back(clientSocket);
		ClientThread* ct = new ClientThread(clientSocket, &(this->clients));
	}
}

Server::ClientThread::ClientThread(SOCKET clientSocket, client* clientStruct)
: sock(clientSocket), clients(clientStruct) {
	this->buffer = new char[4096];
	this->threadPointer = new std::thread(&Server::ClientThread::Respond, this);
}
Server::ClientThread::~ClientThread() {
	closesocket(this->sock);
	std::vector<SOCKET>* vec = &(this->clients->sockets);
	vec->erase(std::remove(vec->begin(), vec->end(), this->sock));
	this->clients->dict.erase(this->sock);
	threadPointer->detach();

	delete this->threadPointer;
	delete[] this->buffer;
}

void Server::ClientThread::Respond() {
	this->clients->welcomeHandler(this->sock);
	while (true) {
		memset(this->buffer, 0, 4096);

		int bytesRecieved = recv(this->sock, this->buffer, 4096, 0);
		if (bytesRecieved == SOCKET_ERROR) {
			break;
		}
		if (bytesRecieved == 0) {
			break;
		}
		this->clients->receiveHandler(this->sock, (const char*)this->buffer, bytesRecieved);
	}
	this->clients->disconnectHandler(this->sock);
	delete this;
}