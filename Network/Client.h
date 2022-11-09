#pragma once
#include <thread>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <functional>
#pragma comment(lib, "ws2_32.lib")

#define CLIENT_OPEN 1
#define CLIENT_CONNECTING 2
#define CLIENT_CLOSED 3
#define CLIENT_WINSOCK_ERROR 4
#define CLIENT_SOCKET_ERROR 5
#define CLIENT_CONNECT_ERROR 6

class Client
{
	public:
		Client(std::string IPaddress, uint16_t port, std::function<void()> receiverHandlerLambda);
		~Client();
		void RefreshConnection();
		void CloseConnection();
		void Send(const char* bytes, int size);
		int GetStatus();
		const char* GetBufferPtr();

	private:
		void ReceiveThread();
		void RefreshConnectionThread();

		int status = CLIENT_CLOSED;
		std::function<void()> receiveHandler;
		std::thread* receiveThreadPtr = nullptr;
		std::thread* refreshConnectionThreadPtr = nullptr;
		char* buffer = nullptr;
		SOCKET sock;
		std::string IP;
		const uint16_t port;
};

