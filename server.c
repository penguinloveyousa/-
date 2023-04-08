// 引入头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
// 定义常量
#define PORT 8888 // 监听端口
#define BUF_SIZE 1024 // 缓冲区大小

// 初始化套接字库
void init_winsock() 
{
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) 
	{
        printf("初始化套接字库失败！\n");
        exit(1);
    }
}

// 创建套接字
SOCKET create_socket() 
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) 
	{
        printf("创建套接字失败！\n");
        WSACleanup();
        exit(1);
    }
    return sock;
}

// 绑定地址
void bind_address(SOCKET sock) 
{
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) 
	{
        printf("绑定地址失败！\n");
        closesocket(sock);
        WSACleanup();
        exit(1);
    }
}

// 监听端口
void listen_port(SOCKET sock) 
{
    if (listen(sock, SOMAXCONN) == SOCKET_ERROR) 
	{
        printf("监听端口失败！\n");
        closesocket(sock);
        WSACleanup();
        exit(1);
    }
	printf("等待连接······");
}

// 接受客户端连接
SOCKET accept_client(SOCKET sock) 
{
    struct sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);
    SOCKET client_sock = accept(sock, (struct sockaddr *)&client_addr, &client_addr_size);
    if (client_sock == INVALID_SOCKET)
	{
        printf("接受客户端连接失败！\n");
        closesocket(sock);
        WSACleanup();
        exit(1);
    }
    printf("客户端已连接，IP地址：%s，端口号：%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    return client_sock;
}

// 收发数据
void communicate(SOCKET client_sock) 
{
    char buf[BUF_SIZE];
    int recv_len;
    while (1) 
	{
        // 接收客户端消息
        recv1:recv_len = recv(client_sock, buf, BUF_SIZE, 0);
        if (recv_len > 0) 
		{
			char reply[255];
            buf[recv_len] = '\0';
            printf("收到客户端消息：%s\n", buf);

            // 回复客户端消息
			printf("请回复：");
            gets(reply);
            send(client_sock, reply , strlen(reply), 0);
            printf("回复客户端消息：%s\n", buf);

            // 如果收到"bye"，则结束通信
            if (strcmp(buf, "bye") == 0) 
			{
                break;
            }
        } 
		else if (recv_len == 0) 
		{
            printf("客户端已断开连接！\n");
            break;
        } 
		else 
		{
            printf("接收数据失败！\n");
            break;
        }
    }
}

// 关闭套接字
void close_socket(SOCKET sock) 
{
    closesocket(sock);
}

// 清理套接字库
void cleanup_winsock() 
{
    WSACleanup();
}

int main() {
    // 初始化套接字库
    init_winsock();

    // 创建套接字
    SOCKET server_sock = create_socket();

    // 绑定地址
    bind_address(server_sock);

    // 监听端口
    listen_port(server_sock);

    // 接受客户端连接
    SOCKET client_sock = accept_client(server_sock);

    // 收发数据
    communicate(client_sock);

    // 关闭套接字
    close_socket(client_sock);
    close_socket(server_sock);

    // 清空
	return 0;
}