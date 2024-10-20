
#ifndef SERVER_H
#define SERVER_H
#include <winsock2.h>  
#include <ws2tcpip.h>  
#include <iostream>  
#include <string>  
#include <thread>  

#pragma comment(lib, "Ws2_32.lib")  

extern const int PORT;  
extern std::string sharedString;  

void handleClient(SOCKET clientSocket);
int run_server();
#endif
