#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#define MAX 100

int app(char ipnum[],char hename[]);
extern char* myname(char* myname);
int server();
int pblove();
int api();
//char center[30];
void caidan() {
	printf("\n----------------------------------------------------");printf("\n");
	printf("|                                                  |");printf("\n");
	printf("|              1、显示联系人发送信息               |");printf("\n");
	printf("|              2、接收信息等待模式                 |");printf("\n");
	printf("|              3、添加联系人                       |");printf("\n");
	printf("|              4、删除联系人                       |");printf("\n");
	printf("|              5、清空联系人                       |");printf("\n");
	printf("|              666、显示特别关心                   |");printf("\n");
	printf("|              0、退出通讯录                       |");printf("\n");
	printf("|                                                  |");printf("\n");
	printf("|    powered by 彭博、叶桐、孙皓宇||盗用必究       |");printf("\n");
	printf("|                                                  |");printf("\n");
	printf("----------------------------------------------------\n");
	api();
//	printf("1、显示联系人\n");
//	printf("2、接收信息\n");
//	printf("3、添加联系人\n");
//	printf("4、删除联系人\n");
//	printf("5、清空联系人\n");
//	printf("666、显示特别关心\n");
//	printf("0、退出通讯录\n");
//	printf("\n\npowered by 彭博、叶桐、孙皓宇||盗用必究\n\n");
}


struct per {
	char name[20];
	int gender;
	char numeber[30];
	int lo;//特别关心参数
	struct per* next;
};//采用链表进行处理

//struct book {
//	struct per p[MAX];
//	int c;
//};
//struct book myb;


int  sendnum() {		//发送信息打印模块
	int num = 0;
	printf("请选择要对话人的序号：");
	scanf("%d", &num);
	return num;//对接叶桐
}

void fasong(int num,struct per*head) {			//发送信息及对接模块
	system("cls");
	int qs = 0;
	if(num == 0) {
		printf("请先去选择发送信息对象:\n");
		system("pause");
		system("cls");
	}
	else{
		struct per* p = head->next;
		//		printf("")
		int find = 1;
		while (p) {									//遍历链表查找对应元素
			if (find == num) break;					//找到此就可以返回指针
			find++;
			p = p->next;
		}
		printf("请问是否给%s发信息\n1是0否",p->name);
		scanf("%d",&qs);
		if(qs == 0) system("cls");
		else{
			system("cls");
			//			printf("转到叶桐界面");
			app(p->numeber,p->name);
		}
		
	}
	
	
	//先显示联系人，再按2键
}


void xian(struct per* head) {		//显示通讯录模块
	
	//printf("通讯录共有%d人\n", myb->c);
	//int num = 0;
	//for (int i = 0; i < myb->c; i++) {
	//	num++;
	//	printf("%d、", num);
	//	printf("%-20s", myb->p[i].name);
	//	myb->p[i].gender == 1 ? printf("%-20s", "男") : printf("%-20s", "女");
	//	printf("%-20s", myb->p[i].numeber);
	//	myb->p[i].lo == 1 ? printf("%-20s", "特别关心") : printf("%-20s", "否");
	//	printf("\n");
	//}
	struct per* p = head->next;
	if(p == NULL){
		printf("没有联系人\n");
		system("pause");
		system("cls");
	}else{
		int num = 1;
		while (p) {
			printf("%d、", num);
			printf("%-20s", p ->name);
			p->gender == 1 ? printf("%-20s", "男") : printf("%-20s", "女");
			printf("%-20s", p->numeber);
			p->lo == 1 ? printf("%-20s", "特别关心") : printf("%-20s", "否");
			printf("\n");
			p = p->next;
			num++;
		}
		printf("是否发送信息？1发送 0返回主界面  \n选择  ");
		int choo;
		scanf("%d", &choo);
		if (choo) {
			fasong(sendnum(),head);
		}
		else 	system("cls");
	}
	
}

//int findlove(){					//查找特别关心对应序号
//	printf("\n请输入要对话的序号");
//	int lovetemp = 0;
//	scanf("%d",&lovetemp);
//	int lovef = 0;
//	for (int i = 0; i < myb.c; i++) {
//		if(myb.p[i].lo == 1){
//				lovef++;
//			if(lovetemp == lovef){
//				return i + 1;
//			}
//		}
//		
//	}
//	
//}

int findLove(struct per* head) {				//查找特别关心对应序号
	printf("\n请输入要对话的序号");
	struct per* p = head->next;
	int choose = 0;
	scanf("%d", &choose);
	int num = 0;
	int ans = 0;
	while (p) {
		ans++;
		if (p->lo == 1) {
			num++;
			if (choose == num) {
				return ans;
			}
		}
		p = p->next;
	}
	return 0;
}
void loves(struct per* head){				//显示特别关心模块
	pblove();
	printf("\n正在为您进入专属空间");
	Sleep(1000);
	printf(".");
	Sleep(1000);
	printf(".\n");
//	Sleep(1000);
//	printf(".");
//	Sleep(1000);
	//	system("pause");
//	int num = 0;
	//for (int i = 0; i < myb->c; i++) {
	//	if(myb->p[i].lo == 1){
	//		num++;
	//		printf("%d、", num);
	//		printf("%-20s", myb->p[i].name);
	//		myb->p[i].gender == 1 ? printf("%-20s", "男") : printf("%-20s", "女");
	//		printf("%-20s", myb->p[i].numeber);
	//		myb->p[i].lo == 1 ? printf("%-20s", "特别关心") : printf("%-20s", "否");
	//		printf("\n");
	//	}
	
	//}
	
	struct per* p = head->next;
	
	int num = 1;
	while (p) {
		if (p->lo == 1) {
			printf("%d、", num);
			printf("%-20s", p->name);
			p->gender == 1 ? printf("%-20s", "男") : printf("%-20s", "女");
			printf("%-20s", p->numeber);
			p->lo == 1 ? printf("%-20s", "特别关心") : printf("%-20s", "否");
			printf("\n");
			num++;
		}
		p = p->next;
	}
	num--;
	printf("特别关心共有%d人\n", num);
	printf("是否发送信息？1发送 0返回主界面  选择");
	int choo;
	scanf("%d", &choo);
	if (choo) {
		fasong(findLove(head),head);
	}
	else 	system("cls");
}

int ergodicity(struct per* head) {
	struct per* p = head->next;
	int num = 0;
	while (p) {
		num++;
		p = p->next;
	}
	return num;
}
void ffpr(struct per*head) {		//写入模块
	int c = 0;
	FILE* fp, * temp;
	if (!(fp = temp = fopen("./ab.txt", "w"))) printf("文件打开错误");
	c = ergodicity(head);
	fprintf(fp, "%d\n", c);
	//for (int i = 0; i < c; i++) {
	//	fprintf(fp, "%-20s", myb.p[i].name);
	//	myb.p[i].gender == 1 ? fprintf(fp, "%-20d", 1) : fprintf(fp, "%-20d", 2);
	//	myb.p[i].lo == 1 ? fprintf(fp, "%-20d", 1) : fprintf(fp, "%-20d", 0);
	//	fprintf(fp, "%-20s", myb.p[i].numeber);
	//	fprintf(fp, "%s", "\n");
	//	//		fseek(fp,1,1);
	//}
	struct per* p = head->next;
	while (p) {
		fprintf(fp, "%-20s", p->name);
		p->gender== 1 ? fprintf(fp, "%-20d", 1) : fprintf(fp, "%-20d", 2);
		p->lo == 1 ? fprintf(fp, "%-20d", 1) : fprintf(fp, "%-20d", 0);
		fprintf(fp, "%-20s", p->numeber);
		fprintf(fp, "%s", "\n");
		p = p->next;
	}
	fclose(fp);
}

void ffsc(struct per*head) {		//读取模块				//传入初始化的头指针head;
	FILE* fp, * temp;
	//fp = temp = fopen("./ab.txt", "r");
	if (!(fp = temp = fopen("./ab.txt", "r"))) printf("文件打开错误");
	/*fscanf(fp, "%d", &myb.c);*/
	/*int i = 0;
	  while (i < myb.c) {
	  fscanf(fp, "%s", myb.p[i].name);
	  char ch;
	  while ((ch = fgetc(fp)) == ' ');
	  fseek(fp, -1, 1);
	  fscanf(fp, "%d", &myb.p[i].gender);
	  while ((ch = fgetc(fp)) == ' ');
	  fseek(fp, -1, 1);
	  fscanf(fp, "%d", &myb.p[i].lo);
	  while ((ch = fgetc(fp)) == ' ');
	  fseek(fp, -1, 1);
	  fscanf(fp, "%s", myb.p[i].numeber);
	  i++;
	  }*/
	
	int i=1,count = 0;
	fscanf(fp, "%d", &count);
	struct per* p = (struct per*)malloc(sizeof(struct per));		//必须先至少申请一个空间
	if(count == 0) free(p);
	while (i<=count) {
		if(i == 1) head->next = p;
		fscanf(fp, "%s", p->name);
		char ch;
		while ((ch = fgetc(fp)) == ' ');
		fseek(fp, -1, 1);
		fscanf(fp, "%d", &p->gender);
		while ((ch = fgetc(fp)) == ' ');
		fseek(fp, -1, 1);
		fscanf(fp, "%d", &p->lo);
		while ((ch = fgetc(fp)) == ' ');
		fseek(fp, -1, 1);
		fscanf(fp, "%s", p->numeber);
		if (i == count) p->next = NULL;
		else{
			struct per* q = (struct per*)malloc(sizeof(struct per));
			p->next = q;
			p = q;
		}
		i++;
	}
//	xian(head);
	fclose(fp);
}
struct per* last(struct per* head) {						//相当于查找list容器end前一位
	struct per* p = head->next;
	struct per* q = head;
	while (p) {
		q = p;
		p = p->next;
	}
	return q;
}
void put(struct per* head) {		//添加联系人模块
	//int c = myb->c;
	printf("请输入姓名：");
	struct per*	q = last(head);
	struct per* p = (struct per*)malloc(sizeof(struct per));
	q->next = p;
	scanf("%s", p->name);
//	puts(p->name);
	printf("请输入性别1男2女：");
	int te = 0;
	while (1) {
		scanf("%d", &te);
//		printf("执行到这里");
		if (te != 2 && te != 1) printf("有误，请重新输入：");
		else {
			p->gender = te;
			break;
		}
	}
	printf("请输入号码:");
	scanf("%s",p->numeber);
	printf("是否将此联系人设置为特别关心？\n1是 0否\n");
	while (1) {
		scanf("%d", &te);
		if (te != 1 && te != 0) printf("有误，请重新输入：");
		else {
			p->lo = te;
			break;
		}
	}
	printf("完成！");
	/*myb->c++;*/
	p->next = NULL;
	ffpr(head);//导入到文件
	system("pause");
	system("cls");
}


struct per* ifis(char n[], struct per* head) {		//查找某个联系人模块
	//for (int i = 0; i <= myb->c; i++) {
	//	if (!strcmp(myb->p[i].name, n)) { //相等
	//		return i;
	//	}
	//}
	struct per* p = head->next;
	while (p) {
		if (!(strcmp(p->name, n))) {
			return p;
		}
		p = p->next;
	}
	return NULL;//未找到
}

struct per* ffront(struct per* head, struct per* find) {			//寻找链表上一个指针
	struct per* p = head->next;
	while (p) {
		if ((p->next) == find) return p;
		p = p->next;
	}
	return NULL;
}

void shan(struct per* head) {			//删除联系人模块
	printf("请输入要删除的联系人：");
	char temp[30];
	scanf("%s", temp);
	struct per* ans = ifis(temp, head);
	//int c = myb->c;
	if (ans == NULL) {
		printf("不存在这个人\n");
	}
	else {								//执行链表删除操作
		/*for (int i = ans; i + 1 < c; i++) {
		  myb->p[i] = myb->p[i + 1];
		  }
		  myb->c--;*/
		ffront(head, ans)->next = ans->next;
		free(ans);					//释放内存
		printf("删除成功");
		ffpr(head);
	}
	system("pause");
	system("cls");
	
}

void qing(struct per* head) {			//清空联系人模块
	printf("此次操作只会剩下一个本机地址！！！确认清空吗？！！！按1确认 0取消\n");
	int qs = 0;
	scanf("%d", &qs);
	if (qs) {
		/*myb->c = 0;*/
		free(head->next);							//释放内存
		head->next = NULL;
		FILE* fp;
		if (!(fp = fopen("./ab.txt", "w"))) printf("文件打开错误");
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



int pbmain(char pbhy[]) {				//此文件主函数
	struct per* head = (struct per*)malloc(sizeof(struct per));
	//printf("您的输入有误，请重新输入\n");
	int s = 0;
	//myb.c = 0;
	head->next = NULL;
	ffsc(head);
	//初始化头
	myname(pbhy);
	while (1) {
		caidan();
		printf("\n");
		printf("选择：");
		scanf("%d", &s);
		switch (s) {
		case 0:
			return 0;
			break;
			case 1:xian(head);
			break;
			case 2:server();
			break;
			case 3:put(head);
			break;
			case 4:shan(head);
			break;
			case 5:qing(head);
			break;
			case 666:loves(head);
			break;
		default:
			printf("您的输入有误，请重新输入\n");
			system("pause");
			system("cls");
		}
	}
	return 0;
}