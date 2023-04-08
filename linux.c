// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8888 // 服务端监听的端口号
#define MAXLINE 1024 // 缓冲区大小

int main()
{
    int listenfd, connfd; // 监听套接字和连接套接字
    struct sockaddr_in servaddr, cliaddr; // 服务端和客户端的地址结构
    socklen_t cliaddr_len; // 客户端地址长度
    char buf[MAXLINE]; // 缓冲区
    int n; // 读写的字节数

    // 创建一个TCP套接字
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) 
    {
        perror("套接字创建错误！");
        exit(1);
    }

    // 初始化服务端地址结构
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET; // IPv4协议
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 任意本地地址
    servaddr.sin_port = htons(PORT); // 指定端口号

    // 绑定套接字和地址
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
    {
        perror("绑定错误！");
        exit(1);
    }

    // 监听套接字，设置最大连接数为20
    if (listen(listenfd, 20) < 0) 
    {
        perror("监听错误！");
        exit(1);
    }

    printf("等待连接中······\n");

    while (1) {
        // 接受客户端的连接请求，返回一个新的连接套接字
        cliaddr_len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
        if (connfd < 0) 
        {
            perror("接收错误！");
            continue;
        }

        // 打印客户端的地址信息
        printf("连接到ip: %s和端口: %d\n",inet_ntop(AF_INET, &cliaddr.sin_addr, buf, sizeof(buf)),ntohs(cliaddr.sin_port));

        while (1) 
        {
            // 从连接套接字中读取客户端发送的消息
            n = read(connfd, buf, MAXLINE);
            if (n == 0) 
            {
                printf("客户端已关闭！\n");
                break;
            }
            else if (n < 0) 
            {
                perror("读取错误！");
                break;
            }
            else
            {
                printf("客户端发来的消息: %s\n", buf);

                // 将消息原样回复给客户端
                char reply[255];
                printf("请回复：");
                // scanf("%s",reply);

                printf("回复的信息是:%s",reply);
                n = write(connfd, reply, n);
                if (n < 0) 
                {
                    perror("写入错误！");
                    break;
                }
            }
        }

        // 关闭连接套接字
        close(connfd);
    }

    // 关闭监听套接字
    close(listenfd);

    return 0;
}