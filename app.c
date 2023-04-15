// 库文件区
#include <WINSOCK2.H>
#include <STDIO.H>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

// 参数区
#pragma  comment(lib,"ws2_32.lib")
#define IP_ARR ""
#define PORT 9999 //接收端口
#define PORT_SERVER 8888 //发送端口

// 函数区
void WSAsetup() //加载套接字库
{
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		printf("套接字库错误！\n");
		exit(1);
	}
}

SOCKET create_socket() //创建套接字
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) 
	{
        printf("创建套接字失败！\n");
        WSACleanup();
        exit(1);
    }
    return sock;
}

void bind_address_p2p(SOCKET sclient)
{
		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(PORT);
		serAddr.sin_addr.S_un.S_addr = inet_addr(IP_ARR);
		if (connect(sclient, (sockaddr*)& serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{
			printf("连接错误！");
			closesocket(sclient);
			exit(1);
		}
}

void bind_address_server(SOCKET sclient)
{
		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(PORT);
		serAddr.sin_addr.S_un.S_addr = inet_addr(IP_ARR);
		if (connect(sclient, (sockaddr*)& serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{
			printf("连接错误！");
			closesocket(sclient);
			exit(1);
		}
}

void bind_address_servertwo(SOCKET sclient)
{
		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(PORT_SERVER);
		serAddr.sin_addr.S_un.S_addr = inet_addr(IP_ARR);
		if (connect(sclient, (sockaddr*)& serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{
			printf("连接错误！");
			closesocket(sclient);
			exit(1);
		}
}

int socker_p2p()	//客户端点对点通讯函数
{
	SOCKET sclient = create_socket();
	bind_address_p2p(sclient);

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

int sender_p2p()
{
	SOCKET sclient = create_socket();
	bind_address_server(sclient);

	char a[255];
	while(strcmp(a,"bye") != 0)
	{   
        printf("客户端1：");
        gets(a);
		send(sclient, (const char*)(&a) , sizeof(a), 0);
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		char* d = (recData);
		if (ret > 0)
		{
				recData[ret] = 0x00;
				printf("客户端2：");
				printf("%s\n", d);
		}
	}
	closesocket(sclient);
	WSACleanup();
	return 1;
}

int server_p2p()
{
	SOCKET sclient = create_socket();
	bind_address_servertwo(sclient);

	char a[255];
	while(strcmp(a,"bye") != 0)
	{   
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		char* d = (recData);
		if (ret > 0)
		{
				recData[ret] = 0x00;
				printf("客户端1：");
				printf("%s\n", d);
		}
		printf("客户端2：");
        gets(a);
		send(sclient, (const char*)(&a) , sizeof(a), 0);
	}
	closesocket(sclient);
	WSACleanup();
	return 1;
}

int main()
{
	WSAsetup();
	int choose = 0;
	int status = 0;
	inputerror:
	printf("1.点对点 2.转发发送 3.转发接收\n");
	scanf("%d",&choose);
	getchar();
	switch (choose)
	{
	case 1:
		status = socker_p2p();
		break;
	case 2:
		status = sender_p2p();
		break;
	case 3:
		status = server_p2p();
	default:
		printf("输入错误！");
		system("cls");
		goto inputerror;
		break;
	}
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
