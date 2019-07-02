#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <Windows.h>
#include <process.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFSIZE 100

unsigned WINAPI ThreadClient(void* arg);

void SendMSG(char* message, int len);

SOCKET clientSock[100];
HANDLE hMutex;

int clientNumber = 0;

int main(int argc, char* argv[]){

	printf("SERVER\n");

	WSADATA wsaData;
	SOCKET ServSock, ClntSock;
	SOCKADDR_IN servAddr, clntAddr;
	int clntAddrSize;
	HANDLE hThread;
	DWORD ThreadID;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	hMutex = CreateMutex(NULL, FALSE, NULL);

	ServSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(30000);

	bind(ServSock, (SOCKADDR*)&servAddr, sizeof(servAddr));

	listen(ServSock, 100);

	while (1) {

		clntAddrSize = sizeof(clntAddr);
		ClntSock = accept(ServSock, (SOCKADDR*)&clntAddr, &clntAddrSize);

		WaitForSingleObject(hMutex, INFINITE);
		clientSock[clientNumber++] = ClntSock;
		ReleaseMutex(hMutex);

		printf("연결된 클라이언트의 수 : %d\n", clientNumber);
		printf("연결된 클라이언트의 IP : %s\n", inet_ntoa(clntAddr.sin_addr));
		printf("연결 가능한 클라이언트의 수 : %d\n", 100 - clientNumber);

		hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadClient, (void*)&ClntSock, 0, (unsigned *)&ThreadID);
	}

	closesocket(ClntSock);
	closesocket(ServSock);
	WSACleanup();
	return 0;
}

unsigned WINAPI ThreadClient(void *arg){

	SOCKET ClntSock = *((SOCKET*)arg);
	int strLen = 0;
	char message[BUFSIZE];
	int i;

	while ((strLen = recv(ClntSock, message, BUFSIZE, 0)) != 0) {
		SendMSG(message, strLen);
	}

	WaitForSingleObject(hMutex, INFINITE);

	for (i = 0; i<clientNumber; i++) {
		if (ClntSock == clientSock[i]) {
			for (; i < clientNumber - 1; i++) {
				clientSock[i] = clientSock[i + 1];
			}
			break;
		}
	}

	clientNumber--;
	ReleaseMutex(hMutex);
	closesocket(ClntSock);

	return 0;
}

void SendMSG(char* message, int len){

	WaitForSingleObject(hMutex, INFINITE);

	for (int i = 0; i < clientNumber; i++) {
		send(clientSock[i], message, len, 0);
	}

	ReleaseMutex(hMutex);
}