#include <winsock2.h>
#include <windows.h>
#include "stdafx.h"
#include <ws2tcpip.h>
#include <iostream>

using namespace std;

int main()
{
	cout << "=============W11 Sockets========================" << endl;
	cout << "=============Client=============================" << endl;
	cout << "=============Step 1 - Setup DLL=================" << endl;
	SOCKET clientSocket;
	int port = 55555;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0)
	{
		cout << "Winsock dll not found!" << endl;
		return 0;
	}
	else
	{
		cout << "Winsock dll FOUND!!!" << endl;
		cout << "The status: " << wsaData.szSystemStatus << endl;

	}



	cout << "=============Step 2 - Setup Client Socket=======" << endl;
	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else
	{
		cout << "socket() is OK!" << endl;
	}

	cout << "=====Step 3 - Connect with the server socket====" << endl;
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		cout << "Client: connect() - Failed to Connect" << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "Client: Connect() is OK!" << endl;
		cout << "Client: Can start sending and recieving data" << endl;

	}

	cout << "=============Step 4 - Chat to the Server=================" << endl;

	char buffer[200];
	cout << "Please enter a message to send to the Server: ";
	cin.getline(buffer, 200);



	int byteCount = send(clientSocket, buffer, 200, 0);

	if(byteCount > 0)
	{
		cout << "Message sent: "<< buffer << endl;
	}
	else 
	{
		cout << "Send failed, WSA cleanup initiating"<<endl;
		WSACleanup();
	}






	cout << "=============Step 5 - Close Socket=================" << endl;


	system("pause");
	WSACleanup();
	return 0;



	

}
