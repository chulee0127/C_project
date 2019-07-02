#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>

#define BUF_SIZE 100
#define NAME_SIZE 20

unsigned WINAPI SendMsg(void* arg);
unsigned WINAPI RecvMsg(void* arg);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[]) {

	WSADATA wsaData;
	SOCKET hSock;
	SOCKADDR_IN servAdr;
	HANDLE hSndThread, hRcvThread;
	char a[10];

	printf("닉네임을 입력하세요 : ");
	scanf("%s", &a);

	printf("%s 님이 입장하셨습니다\n", a);

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sprintf(name, "[%s]", a);

	hSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAdr.sin_port = htons(30000);

	connect(hSock, (SOCKADDR*)&servAdr, sizeof(servAdr));

	hSndThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&hSock, 0, NULL);

	hRcvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&hSock, 0, NULL);

	WaitForSingleObject(hSndThread, INFINITE);
	WaitForSingleObject(hRcvThread, INFINITE);

	closesocket(hSock);
	WSACleanup();

	return 0;
}

unsigned WINAPI SendMsg(void* arg) {

	SOCKET hSock = *((SOCKET*)arg);
	char nameMsg[NAME_SIZE + BUF_SIZE];

	printf("대화창 종료를 원하시면 q 혹은 Q 버튼을 눌러주세요\n");

	while (1) {

		fgets(msg, BUF_SIZE, stdin);

		printf("\n");

		if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")) {
			closesocket(hSock);
			exit(0);
		}

		sprintf(nameMsg, "%s %s", name, msg);
		send(hSock, nameMsg, strlen(nameMsg), 0);
	}

	printf("\n");
	return 0;
}

unsigned WINAPI RecvMsg(void* arg) {

	int hSock = *((SOCKET*)arg);
	char nameMsg[NAME_SIZE + BUF_SIZE];
	int strLen;

	while (1) {

		strLen = recv(hSock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);

		if (strLen == -1)
			return -1;

		nameMsg[strLen] = 0;
		fputs(nameMsg, stdout);
		printf("\n");
	}

	return 0;
}