#include <winsock2.h>  
#include <ws2tcpip.h>  
#include <iostream>  
#include <string>  

#pragma comment(lib, "Ws2_32.lib")  

const char* SERVER_ADDRESS = "192.168.5.119";  
const int PORT = 11451;  

std::string server_string;
std::string send_string;
int run_chient(bool flag = false) {  
	server_string.clear();
	WSADATA wsaData;  
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);  
	if (result != 0) {  
		std::cerr << "[ERR]连接失败: " << result << std::endl;  
		return 1;  
	}  
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
	if (clientSocket == INVALID_SOCKET) {  
		std::cerr << "[ERR]在socket()处错误: " << WSAGetLastError() << std::endl;  
		WSACleanup();  
		return 1;  
	}  
	//std::cout<<"[info]正在准备连接..."<<std::endl;
	sockaddr_in serverAddr;  
	serverAddr.sin_family = AF_INET;  
	serverAddr.sin_port = htons(PORT);  
	inet_pton(AF_INET, SERVER_ADDRESS, &serverAddr.sin_addr);  
	
	if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {  
		std::cerr << "[ERR]连接终止: " << WSAGetLastError() << std::endl;  
		closesocket(clientSocket);  
		WSACleanup();  
		return 1;  
	}  
	
	char buffer[1024];  
	int bytesReceived;  
	
	// Receive initial string from server  
	bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);  
	if (bytesReceived <= 0) {  
		std::cerr << "[ERR]无法从 服务器接收数据。" << std::endl;  
		closesocket(clientSocket);  
		WSACleanup();  
		return 1;  
	}  
	buffer[bytesReceived] = '\0';  
	for(int i = 0;i < (int)strlen(buffer);i++){
		server_string.push_back(buffer[i]);
	}
	//if(!flag) std::cout << "[info]成功从服务端接收数据: \n"  << std::endl;  //<< buffer
	if(!flag) return 0; 
	重新尝试:
		std::string input;  
		//std::cout << "Enter new string to send to server: ";  
		//std::getline(std::cin, input);  
		input = send_string;
		// Send new string to server  
		send(clientSocket, input.c_str(), input.size(), 0);  
		
		// Optionally, receive updated string from server  
		bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);  
		if (bytesReceived > 0) {  
			buffer[bytesReceived] = '\0';  
			//std::cout << "[info]服务端数据更新成功: " <<  std::endl;  //buffer <<
		} else {  
			std::cout << "[WAR]更新失败：服务端停止读入，是否挂起重新尝试？1/0" << std::endl; 
			bool turn;
			std::cin>>turn;
			if(turn) goto 重新尝试;
		}  
	
	closesocket(clientSocket);  
	WSACleanup();  
	return 0;  
}
