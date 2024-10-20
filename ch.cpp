#include <winsock2.h>  
#include <ws2tcpip.h>  
#include <iostream>  
#include <string>  

#pragma comment(lib, "Ws2_32.lib")  

const char* SERVER_ADDRESS = "192.168.5.119";  
const int PORT = 1145;  

int main() {  
	WSADATA wsaData;  
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);  
	if (result != 0) {  
		std::cerr << "WSAStartup failed: " << result << std::endl;  
		return 1;  
	}  
	
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
	if (clientSocket == INVALID_SOCKET) {  
		std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;  
		WSACleanup();  
		return 1;  
	}  
	
	sockaddr_in serverAddr;  
	serverAddr.sin_family = AF_INET;  
	serverAddr.sin_port = htons(PORT);  
	inet_pton(AF_INET, SERVER_ADDRESS, &serverAddr.sin_addr);  
	
	if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {  
		std::cerr << "connect failed: " << WSAGetLastError() << std::endl;  
		closesocket(clientSocket);  
		WSACleanup();  
		return 1;  
	}  
	
	char buffer[1024];  
	int bytesReceived;  
	
	// Receive initial string from server  
	bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);  
	if (bytesReceived <= 0) {  
		std::cerr << "Failed to receive data from server." << std::endl;  
		closesocket(clientSocket);  
		WSACleanup();  
		return 1;  
	}  
	buffer[bytesReceived] = '\0';  
	std::cout << "Initial string from server: " << buffer << std::endl;  
	
	while (true) {  
		std::string input;  
		std::cout << "Enter new string to send to server: ";  
		std::getline(std::cin, input);  
		
		// Send new string to server  
		send(clientSocket, input.c_str(), input.size(), 0);  
		
		// Optionally, receive updated string from server  
		bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);  
		if (bytesReceived > 0) {  
			buffer[bytesReceived] = '\0';  
			std::cout << "Updated string from server: " << buffer << std::endl;  
		} else {  
			std::cout << "Server closed connection." << std::endl;  
			break;  
		}  
	}  
	
	closesocket(clientSocket);  
	WSACleanup();  
	return 0;  
}
