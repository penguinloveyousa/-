// linux.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 8888 // 服务端监听的端口号
#define PORT_FOR 9999
#define MAXLINE 1024 // 缓冲区大小
#define IP_ADDR ""
// 设置超时时间为10秒
#define TIMEOUT 10

// accept函数的超时版本
int accept_timeout(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int ret;
    fd_set accept_fdset;
    struct timeval timeout;

    FD_ZERO(&accept_fdset);
    FD_SET(sockfd, &accept_fdset);
    timeout.tv_sec = TIMEOUT;
    timeout.tv_usec = 0;

    do 
    {
        ret = select(sockfd + 1, &accept_fdset, NULL, NULL, &timeout);
    } 
    while (ret == -1 && errno == EINTR);

    if (ret == -1) 
    {
        perror("select error");
        return -1;
    } 
    else if (ret == 0) 
    {
        // 超时了
        errno = ETIMEDOUT;
        return -1;
    } 
    else 
    {
        ret = accept(sockfd,addr,addrlen);
        if (ret == -1) 
        {
            perror("接收错误！456");
            return -1;
        }
        return ret;
    }
}

int p2p(int connfd,char* buf)
{
    int n;
        n = read(connfd, buf, MAXLINE);
        if (n == 0) 
            {
                printf("客户端已关闭！\n");
                return 1;
            }
            else if (n < 0) 
            {
                perror("读取错误！");
                return 0;
            }
            else
            {
                printf("客户端发来的消息: %s\n", buf);
                // 回复消息
                char reply[255];
                printf("请回复：");
                fgets(reply,sizeof(reply),stdin);
                printf("回复的信息是:%s",reply);
                n = write(connfd, reply, n);
                if (n < 0) 
                {
                    perror("写入错误！");
                    return 0;
                }
            }
} 
int forward(int connfd,int connfdtwo,char* buf,char* buffor)
{
    int n;
        n = read(connfd, buf, MAXLINE);
        if (n == 0) 
            {
                printf("客户端1已关闭！\n");
                return 0;
            }
            else if (n < 0) 
            {
                perror("读取错误！\n");
                return 0;
            }
            else
            {
                printf("客户端1发来的消息: %s\n", buf);
                char reply[255];
                strcpy(reply,buf);
                printf("转发给客户端2的信息是:%s\n", reply);
                n = write(connfdtwo, reply, n);
                if (n < 0) 
                {
                    perror("写入错误！\n");
                    return 0;
                }
                n = read(connfdtwo, buffor, n);
                if (n == 0)
                {
                    printf("客户端2已关闭！\n");
                    return 0;
                }
                else if (n < 0)
                {
                    perror("读取错误！\n");
                    return 0;
                }
                else 
                {
                    printf("客户端2发来的消息：%s\n", buffor);
                    strcpy(reply,buffor);
                    printf("转发给客户端1的信息是：%s\n",reply);
                    n = write(connfd, reply, n);
                    if (n < 0)
                    {
                        perror("写入错误！\n");
                        return 0;
                    }
                }
            }
            
}

int main()
{
    int listenfd, connfd ,forwardfd ,connfdtwo; // 监听套接字和连接套接字
    struct sockaddr_in servaddr, cliaddr ,forwardaddr ,cliaddrtwo; // 服务端和客户端的地址结构
    char buf[MAXLINE]; // 缓冲区
    char buffor[MAXLINE];
    int n; // 读写的字节数

    // 创建一个TCP套接字
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    forwardfd = socket(AF_INET,SOCK_STREAM, 0);
    if (listenfd < 0 || forwardfd < 0) 
    {
        perror("套接字创建错误！");
        exit(1);
    }

    // 初始化服务端地址结构
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&forwardaddr, 0,sizeof(forwardaddr));
    servaddr.sin_family = AF_INET; // IPv4协议
    forwardaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 任意本地地址
    forwardaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT_FOR); // 指定端口号
    forwardaddr.sin_port = htons(PORT);

    int optval = 1; // 设置optval为TRUE
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)); // 设置SO_REUSEADDR选项
    
    // 绑定套接字和地址
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 || bind(forwardfd, (struct sockaddr *)&forwardaddr, sizeof(forwardaddr)) < 0) 
    {
        perror("绑定错误！");
        exit(1);
    }
    int stdc = listen(forwardfd, 20);
    // 监听套接字，设置最大连接数为20
    if (listen(listenfd, 20) < 0 || stdc < 0) 
    {
        perror("监听错误！");
        exit(1);
    }
    int mode = 0;

    printf("等待连接中······\n");
    
    // 接受客户端的连接请求，返回一个新的连接套接字
        socklen_t cliaddr_len,cliaddrtwo_len; // 客户端地址长度
        cliaddr_len = sizeof(cliaddr);
        cliaddrtwo_len = sizeof(cliaddrtwo);
    while (1) 
    {
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
        connfdtwo = accept_timeout(forwardfd, (struct sockaddr *)&cliaddrtwo, &cliaddrtwo_len);
        if (connfd < 0) 
        {
            perror("接收错误！123");
            break;
        }

        if (connfdtwo == -1) 
        {
            if (errno == ETIMEDOUT) 
            {
                // 超过10s未被连接，把变量mode设为1
                mode = 1;
                printf("超时10s！进入点对点通讯模式！\n");
            } 
            else 
            {
                perror("接收错误！789");
            }
            // continue;
        }
        if (connfdtwo > 0)
        {
            mode = 2;
        }

        if (mode == 1)
        {
            // 打印客户端的地址信息
            printf("连接到ip: %s和端口: %d\n",inet_ntop(AF_INET, &cliaddr.sin_addr, buf, sizeof(buf)),ntohs(cliaddr.sin_port));
        }
        if (mode == 2)
        {
            printf("连接到ip: %s和端口: %d\n",inet_ntop(AF_INET, &cliaddr.sin_addr, buf, sizeof(buf)),ntohs(cliaddr.sin_port));
            printf("连接到ip: %s和端口: %d\n",inet_ntop(AF_INET, &cliaddrtwo.sin_addr, buffor, sizeof(buffor)),ntohs(cliaddrtwo.sin_port));
        }
        int n=1;
        while (1) 
        {
            // 从连接套接字中读取客户端发送的消息
            if (mode == 1) n = p2p(connfd,buf);
            if (mode == 2) n = forward(connfd,connfdtwo,buf,buffor);
            if (n == 1) break;
            if (n == 0) 
            {
                close(connfd);
                close(connfdtwo);
                close(listenfd);
                close(forwardfd);
                return 0;
            }
        }
        // 关闭连接套接字
    close(connfd);
    close(connfdtwo);
    }
    // 关闭监听套接字
    close(listenfd);
    close(forwardfd);
    return 0;
}