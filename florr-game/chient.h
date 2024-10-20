#ifndef CHIENT_H
#define CHIENT_H
#include <winsock2.h>  
#include <ws2tcpip.h>  
#include <iostream>  
#include <string>  
#include "chient.h"
#pragma comment(lib, "Ws2_32.lib")  

extern const char* SERVER_ADDRESS;  
extern int PORT;  

extern std::string server_string;
extern std::string send_string;
int run_chient(bool flag = 0);
#endif
