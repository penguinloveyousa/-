#include"pb.h"
#include"pblove.h"
#include"login.h"
#include"app.h"
#include"server.h"
#include"pbkey.h"

int main() {
	pbkey();
	char* pbhy = (char*)malloc(21 * sizeof(char));
	login_register(pbhy);
	printf("\n欢迎您%s！！！\n", pbhy);
	system("pause");
	system("cls");
	pbmain(pbhy);
	return 0;
}	
