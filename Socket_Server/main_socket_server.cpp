#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <WinSock2.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32")

#define PORT		4578
#define PACKET_SIZE 1024


int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	SOCKET hListen;
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tListenAddr = {};
	tListenAddr.sin_family = AF_INET;
	tListenAddr.sin_port = htons(PORT);
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
	listen(hListen, SOMAXCONN);

	SOCKADDR_IN tClntAddr = {};
	int iClntSize = sizeof(tClntAddr);
	SOCKET hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);

	while (1)
	{

		//char cBuffer[PACKET_SIZE] = {};
		//recv(hClient, cBuffer, PACKET_SIZE, 0);
		//printf("Recv Msg : %s \n", cBuffer);



		char cMsg[] = "Server Send";
		send(hClient, cMsg, strlen(cMsg), 0);

		Sleep(1000);
	}


	closesocket(hClient);
	closesocket(hListen);


	WSACleanup();

	getchar();

	return 0;
}