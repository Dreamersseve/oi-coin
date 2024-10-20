#include <winsock2.h>  
#include <ws2tcpip.h>  
#include <iostream>  
#include <string>  
#include <thread>  
#include "server.h"
#include "rSA.h"
#pragma comment(lib, "Ws2_32.lib")  

int main() {  
	freopen("info.txt","r",stdin);
	getline(cin,sharedString);
	fclose(stdin);
	cout<<"reading info:"<<sharedString<<endl;
	run_server();
}
