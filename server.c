// ����ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
// ���峣��
#define PORT 8888 // �����˿�
#define BUF_SIZE 1024 // ��������С

// ��ʼ���׽��ֿ�
void init_winsock() 
{
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) 
	{
        printf("��ʼ���׽��ֿ�ʧ�ܣ�\n");
        exit(1);
    }
}

// �����׽���
SOCKET create_socket() 
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) 
	{
        printf("�����׽���ʧ�ܣ�\n");
        WSACleanup();
        exit(1);
    }
    return sock;
}

// �󶨵�ַ
void bind_address(SOCKET sock) 
{
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) 
	{
        printf("�󶨵�ַʧ�ܣ�\n");
        closesocket(sock);
        WSACleanup();
        exit(1);
    }
}

// �����˿�
void listen_port(SOCKET sock) 
{
    if (listen(sock, SOMAXCONN) == SOCKET_ERROR) 
	{
        printf("�����˿�ʧ�ܣ�\n");
        closesocket(sock);
        WSACleanup();
        exit(1);
    }
	printf("�ȴ����ӡ�����������");
}

// ���ܿͻ�������
SOCKET accept_client(SOCKET sock) 
{
    struct sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);
    SOCKET client_sock = accept(sock, (struct sockaddr *)&client_addr, &client_addr_size);
    if (client_sock == INVALID_SOCKET)
	{
        printf("���ܿͻ�������ʧ�ܣ�\n");
        closesocket(sock);
        WSACleanup();
        exit(1);
    }
    printf("�ͻ��������ӣ�IP��ַ��%s���˿ںţ�%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    return client_sock;
}

// �շ�����
void communicate(SOCKET client_sock) 
{
    char buf[BUF_SIZE];
    int recv_len;
    while (1) 
	{
        // ���տͻ�����Ϣ
        recv1:recv_len = recv(client_sock, buf, BUF_SIZE, 0);
        if (recv_len > 0) 
		{
			char reply[255];
            buf[recv_len] = '\0';
            printf("�յ��ͻ�����Ϣ��%s\n", buf);

            // �ظ��ͻ�����Ϣ
			printf("��ظ���");
            gets(reply);
            send(client_sock, reply , strlen(reply), 0);
            printf("�ظ��ͻ�����Ϣ��%s\n", buf);

            // ����յ�"bye"�������ͨ��
            if (strcmp(buf, "bye") == 0) 
			{
                break;
            }
        } 
		else if (recv_len == 0) 
		{
            printf("�ͻ����ѶϿ����ӣ�\n");
            break;
        } 
		else 
		{
            printf("��������ʧ�ܣ�\n");
            break;
        }
    }
}

// �ر��׽���
void close_socket(SOCKET sock) 
{
    closesocket(sock);
}

// �����׽��ֿ�
void cleanup_winsock() 
{
    WSACleanup();
}

int main() {
    // ��ʼ���׽��ֿ�
    init_winsock();

    // �����׽���
    SOCKET server_sock = create_socket();

    // �󶨵�ַ
    bind_address(server_sock);

    // �����˿�
    listen_port(server_sock);

    // ���ܿͻ�������
    SOCKET client_sock = accept_client(server_sock);

    // �շ�����
    communicate(client_sock);

    // �ر��׽���
    close_socket(client_sock);
    close_socket(server_sock);

    // ���
	return 0;
}