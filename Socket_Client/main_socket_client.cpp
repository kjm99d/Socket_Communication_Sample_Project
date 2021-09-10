﻿#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")


#define PORT		4578
#define PACKET_SIZE 1024
#define SERVER_IP	"127.0.0.1"


int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	SOCKET hSocket;
	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tAddr = {};
	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(PORT);
	tAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));


	while (1)
	{
		// i want no disconnect;
		// server is packer send

	//	char cMsg[] = "Client Send";
	//	send(hSocket, cMsg, strlen(cMsg), 0);

		char cBuffer[PACKET_SIZE] = {};
		recv(hSocket, cBuffer, PACKET_SIZE, 0);

		printf("Recv Msg : %s \n", cBuffer);
	}
	closesocket(hSocket);

	WSACleanup();

	getchar();

	return 0;
}