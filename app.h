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
#define PORT 9999 //接收端口
#define PORT_SERVER 8888 //发送端口
int app(char ipnum[], char hename[]);