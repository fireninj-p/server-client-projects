#include<winsock2.h>
#include<windows.h>
#include "stdafx.h"
//#include<winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
//#pragma comment(lib, "ws2_32")
using namespace std;
int main(int argc, char* argv[])
{
    cout << "===============w11 sockets===============" << endl;
    cout << "===============Server====================" << endl;
    cout << "=========Step 1 - Set up DLL=============" << endl;
    SOCKET serverSocket, acceptSocket;
    int port = 55555;
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0)
    {
        cout << "The Winsock dll not found" << endl;
        return 0;
    }
    else
    {
        cout << "The Winsock dll succesfully found" << endl;
        cout << "The status: " << wsaData.szSystemStatus << endl;

    }



    cout << "=========Step 2 - Set up Server Socket===" << endl;
    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else 
    {
        cout << "socket() is OK!" << endl;
    }



    cout << "=========Step 3 - Bind Socket============" << endl;
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
    service.sin_port = htons(port);
    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cout << "bind() failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else {
        cout << "bind() is OK!" << endl;
    }



    cout << "=========Step 4 - Initiate Listen========" << endl;
    if (listen(serverSocket, 1) == SOCKET_ERROR)
        cout << "listen():error listening on socket " << WSAGetLastError() << endl;
    else
        cout << "listen() is ok, I'm waiting for connections..." << endl;



    cout << "===Step 5 - Accept Connection from Client=" << endl;


    //SOCKET acceptSocket;
    acceptSocket = accept(serverSocket, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET)
    {
        cout << "accept failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return-1;

    }
    cout << "Accepted Connection" << endl;
    
    cout << "===Step 6 - Chat to the Client===" << endl;
    char buffer[200];

    int byteCount = recv(acceptSocket, buffer, 200);
    
    
    cout << "===Step 7 - Close Socket===" << endl;

    
    
    
    
    
    
    
    system("pause");
    WSACleanup();


}
