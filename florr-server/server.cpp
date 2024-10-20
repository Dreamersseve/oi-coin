#include <winsock2.h>  
#include <ws2tcpip.h>  
#include <iostream>  
#include <string>  
#include <thread>  

#pragma comment(lib, "Ws2_32.lib")  

const int PORT = 11451;  
std::string sharedString;  

void handleClient(SOCKET clientSocket) {  
	char buffer[1024];  
	int bytesReceived;  
	
	// Send initial string to client  
	send(clientSocket, sharedString.c_str(), sharedString.size(), 0);  
	
	while (true) {  
		// Receive data from client  
		bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);  
		if (bytesReceived <= 0) {  
			std::cout << "Client disconnected or error occurred." << std::endl;  
			closesocket(clientSocket);  
			break;  
		}  
		buffer[bytesReceived] = '\0';  
		
		// Update shared string with client input  
		sharedString = buffer;  
		std::cout << "String updated by client: " << sharedString << std::endl;  
		
		// Send updated string back to client (optional)  
		send(clientSocket, sharedString.c_str(), sharedString.size(), 0);  
	}  
}  

int run_server() {  
	WSADATA wsaData;  
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);  
	if (result != 0) {  
		std::cerr << "WSAStartup failed: " << result << std::endl;  
		return 1;  
	}  
	
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
	if (listenSocket == INVALID_SOCKET) {  
		std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;  
		WSACleanup();  
		return 1;  
	}  
	
	sockaddr_in serverAddr;  
	serverAddr.sin_family = AF_INET;  
	serverAddr.sin_port = htons(PORT);  
	serverAddr.sin_addr.s_addr = INADDR_ANY;  
	
	if (bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {  
		std::cerr << "bind failed: " << WSAGetLastError() << std::endl;  
		closesocket(listenSocket);  
		WSACleanup();  
		return 1;  
	}  
	
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {  
		std::cerr << "listen failed: " << WSAGetLastError() << std::endl;  
		closesocket(listenSocket);  
		WSACleanup();  
		return 1;  
	}  
	
	std::cout << "Server listening on port " << PORT << "..." << std::endl;  
	
	while (true) {  
		SOCKET clientSocket = accept(listenSocket, NULL, NULL);  
		if (clientSocket == INVALID_SOCKET) {  
			std::cerr << "accept failed: " << WSAGetLastError() << std::endl;  
			continue;  
		}  
		
		std::thread(handleClient, clientSocket).detach();  
	}  
	
	closesocket(listenSocket);  
	WSACleanup();  
	return 0;  
}
