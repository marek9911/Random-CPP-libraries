#include "Client.h"
#include <iostream>
#include <string>
using namespace std;

Client::Client(std::string IPaddress, uint16_t port, std::function<void()> receiverHandlerLambda)
: IP(IPaddress), port(port), receiveHandler(receiverHandlerLambda) {
	buffer = new char[4096];
	this->RefreshConnection();
}

Client::~Client() {
	this->CloseConnection();
	if (refreshConnectionThreadPtr != nullptr) {
		refreshConnectionThreadPtr->join();
		delete refreshConnectionThreadPtr;
	}
	if (receiveThreadPtr != nullptr) {
		receiveThreadPtr->join();
		delete receiveThreadPtr;
	}
	delete[] buffer;
}

void Client::RefreshConnection() {
	if (refreshConnectionThreadPtr != nullptr) {
		refreshConnectionThreadPtr->join();
		delete refreshConnectionThreadPtr;
		refreshConnectionThreadPtr = nullptr;
	}
	
	refreshConnectionThreadPtr = new thread(&Client::RefreshConnectionThread, this);
}

void Client::CloseConnection() {
	status = CLIENT_CLOSED;
	closesocket(this->sock);
}

void Client::Send(const char* bytes, int size) {
	if (status == CLIENT_OPEN) {
		int sendResult = send(sock, bytes, size, 0);
		if (sendResult == SOCKET_ERROR) {
			status = CLIENT_SOCKET_ERROR;
			this->CloseConnection();
		}
	}
}

int Client::GetStatus() {
	return status;
}

const char* Client::GetBufferPtr() {
	return (const char*)this->buffer;
}

void Client::ReceiveThread() {
	while (status == CLIENT_OPEN) {
		ZeroMemory(buffer, 4096);
		int bytesReceived = recv(this->sock, this->buffer, 4096, 0);
		if (bytesReceived > 0) {
			receiveHandler();
		}
	}

	// Close socket
	this->CloseConnection();
}

void Client::RefreshConnectionThread() {
	status = CLIENT_CONNECTING;
	// Init winsock
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);

	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0) {
		status = CLIENT_WINSOCK_ERROR;
	}

	// Create socket
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sock == INVALID_SOCKET) {
		status = CLIENT_SOCKET_ERROR;
	}

	// Fill in a hint struct
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, IP.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(this->sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR) {
		status = CLIENT_CONNECT_ERROR;
		this->CloseConnection();
	}
	else {
		status = CLIENT_OPEN;
		receiveThreadPtr = new thread(&Client::ReceiveThread, this);
	}
}