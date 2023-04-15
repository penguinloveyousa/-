#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
    char *message = "Hello from client";
    char buffer[MAXLINE];
    int n;

    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 填充服务器地址
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 连接到服务器
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        perror("connection with the server failed");
        exit(EXIT_FAILURE);
    }

    // 发送消息
    n = send(sockfd, message, strlen(message), 0);
    if (n == -1) {
        perror("send failed");
        exit(EXIT_FAILURE);
    }
    printf("Sent %d bytes to server\n", n);

    // 接收回复
    n = recv(sockfd, buffer, MAXLINE, 0);
    if (n == -1) {
        perror("recv failed");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    printf("Received from server: %s\n", buffer);

    // 关闭套接字
    close(sockfd);

    return 0;
}