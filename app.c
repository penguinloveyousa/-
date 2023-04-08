
#include <WINSOCK2.H>
#include <STDIO.H>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>


#pragma  comment(lib,"ws2_32.lib")
#define IP_ARR "82.157.254.160"
#define PORT 8888


int socker()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}

	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET)
	{
		printf("无效的套接字连接！");
		return 0;
	}

	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(PORT);
	serAddr.sin_addr.S_un.S_addr = inet_addr(IP_ARR);
	if (connect(sclient, (sockaddr*)& serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		printf("连接错误！");
		closesocket(sclient);
		return 0;
	}

	char a[255];
	while(strcmp(a,"bye"))
	{   
        printf("<客户端>：");
        gets(a);

		send(sclient, (const char*)(&a) , sizeof(a), 0);
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		char* d = (recData);
		if (ret > 0)
		{
				recData[ret] = 0x00;
				printf("<服务器>：");
				printf("%s\n", d);
		}
	}
	closesocket(sclient);
	WSACleanup();
	return 1;
}

int main()
{
	int status = 0;
	status = socker();
	if (status)
	{
		printf("成功执行！\n");
	}
	if (!status)
	{
		printf("失败！\n");
	}
	return 0;
}
