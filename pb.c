#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX 100
void caidan() {
	printf("1、显示联系人\n");
	printf("2、发送信息\n");
	printf("3、添加联系人\n");
	printf("4、删除联系人\n");
	printf("5、清空联系人\n");
	printf("0、退出通讯录\n");
}


struct per {
	char name[20];
	int gender;
	char numeber[30];
};

struct book {
	struct per p[MAX];
	int c;
};
struct book myb;

void fasong() {

	//先显示联系人，再按2键
}

void ffpr() {
	int c = myb.c;
	FILE* fp, * temp;
	fp = temp = fopen("./ab.txt", "w");
	fprintf(fp, "%d\n", myb.c);
	for (int i = 0; i < c; i++) {
		fprintf(fp, "%-20s", myb.p[i].name);
		myb.p[i].gender == 1 ? fprintf(fp, "%-20d", 1) : fprintf(fp, "%-20d", 2);
		fprintf(fp, "%-20s", myb.p[i].numeber);
		fprintf(fp, "%s", "\n");
		//		fseek(fp,1,1);
	}
	fclose(fp);
}

void ffsc() {
	FILE* fp, * temp;
	fp = temp = fopen("./ab.txt", "r");
	fscanf(fp, "%d", &myb.c);
	int i = 0;
	while (i < myb.c) {
		fscanf(fp, "%s", myb.p[i].name);
		char ch;
		while ((ch = fgetc(fp)) == ' ');
		fseek(fp, -1, 1);
		fscanf(fp, "%d", &myb.p[i].gender);
		while ((ch = fgetc(fp)) == ' ');
		fseek(fp, -1, 1);
		fscanf(fp, "%s", myb.p[i].numeber);
		i++;
	}
	fclose(fp);
}
void put(struct book* myb) {
	int c = myb->c;
	printf("请输入姓名：");
	scanf("%s", myb->p[c].name);
	printf("请输入性别1男2女：");
	int te;
	while (1) {
		scanf("%d", &te);
		if (te != 2 && te != 1) printf("有误，请重新输入：");
		else {
			myb->p[c].gender = te;
			break;
		}
	}
	printf("请输入号码:");
	scanf("%s", myb->p[c].numeber);
	printf("完成！");
	myb->c++;
	ffpr();//导入到文件
	system("pause");
	system("cls");
}

int  sendnum() {
	printf("请选择要对话人的序号：");
	int num = 0;
	scanf("%d", &num);
	return num;//对接叶桐
}

void xian(struct book* myb) {
	printf("通讯录共有%d人\n", myb->c);
	int num = 0;
	for (int i = 0; i < myb->c; i++) {
		num++;
		printf("%d、", num);
		printf("%-20s", myb->p[i].name);
		myb->p[i].gender == 1 ? printf("%-20s", "男") : printf("%-20s", "女");
		printf("%-20s", myb->p[i].numeber);
		printf("\n");
	}
	printf("是否发送信息？1发送 0返回主界面  选择");
	int choo;
	scanf("%d", &choo);
	if (choo) {
		sendnum();
	}
	else 	system("cls");
}
int ifis(char n[], struct book* myb) {
	for (int i = 0; i <= myb->c; i++) {
		if (!strcmp(myb->p[i].name, n)) { //相等
			return i;
		}
	}
	return -1;//未找到
}

void shan(struct book* myb) {
	printf("请输入要删除的联系人：");
	char temp[30];
	scanf("%s", temp);
	int ans = ifis(temp, myb);
	int c = myb->c;
	if (ans == -1) {
		printf("不存在这个人\n");
	}
	else {
		for (int i = ans; i + 1 < c; i++) {
			myb->p[i] = myb->p[i + 1];
		}
		myb->c--;
		printf("删除成功");
		ffpr();
	}
	system("pause");
	system("cls");

}

void qing(struct book* myb) {
	printf("！！！确认清空吗？！！！按1确认 0取消\n");
	int qs = 0;
	scanf("%d", &qs);
	if (qs) {
		myb->c = 0;
		FILE* fp = fopen("./ab.txt", "w");
		fprintf(fp, "%d\n", 0);
		fclose(fp);
		printf("已删除\n");
	}
	else {
		printf("已取消清空操作\n");
	}
	system("pause");
	system("cls");
}



int m() {
	//			printf("您的输入有误，请重新输入\n");用不了！！！！
	int s = 0;
	myb.c = 0;
	ffsc();
	while (1) {
		caidan();
		printf("选择：");
		scanf("%d", &s);
		switch (s) {
		case 0:
			return 0;
			break;
		case 1:xian(&myb);
			break;
		case 2:fasong();
			break;
		case 3:put(&myb);
			break;
		case 4:shan(&myb);
			break;
		case 5:qing(&myb);
			break;
		default:
			printf("您的输入有误，请重新输入\n");
			system("pause");
			system("cls");
		}
	}
}