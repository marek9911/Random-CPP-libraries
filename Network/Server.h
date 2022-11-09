#pragma once
#include <string>
#include <functional>
#include <thread>
#include <vector>
#include <WS2tcpip.h>
#include <map>

#define SERVER_OPEN 1
#define SERVER_CLOSED 2
#define SERVER_WINSOCK_ERROR 3
#define SERVER_SOCKET_ERROR 4

#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")
#else
typedef int SOCKET;
#endif

class Server
{
	public:
		Server(
			uint16_t port, 
			std::function<void(SOCKET clientSocket, const char* bufferPtr, int bytesReceived)> receiverHandlerLambda,
			std::function<void(SOCKET clientSocket)> welcomeHandlerLambda = [](SOCKET){},
			std::function<void(SOCKET clientSocket)> disconnectHandlerLambda = [](SOCKET){}
		);
		~Server();
		void RestartServer();
		void ShutdownServer();
		int GetStatus();
		int GetNumberOfClients();
		std::string GetIPbySocket(SOCKET clientSocket);

		static void Send(SOCKET clientSocket, const char* bytes, int size);
		static void KickClient(SOCKET clientSocket);
		
	private:
		struct client {
			std::vector<SOCKET> sockets;
			std::map<SOCKET, std::string> dict;
			std::function<void(SOCKET clientSocket, const char* bufferPtr, int bytesReceived)> receiveHandler;
			std::function<void(SOCKET clientSocket)> welcomeHandler;
			std::function<void(SOCKET clientSocket)> disconnectHandler;
		} clients;

		class ClientThread
		{
			public:
				ClientThread(SOCKET clientSocket, client* clientStruct);
				~ClientThread();

			private:
				void Respond();

				SOCKET sock;
				char* buffer = nullptr;
				std::thread* threadPointer = nullptr;
				client* clients = nullptr;
		};	

		void Listen();

		SOCKET listeningSocket;
		int status = SERVER_CLOSED;
		const uint16_t port;
		std::thread* listener = nullptr;
};