#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX 100
void caidan() {
	printf("1����ʾ��ϵ��\n");
	printf("2��������Ϣ\n");
	printf("3�������ϵ��\n");
	printf("4��ɾ����ϵ��\n");
	printf("5�������ϵ��\n");
	printf("0���˳�ͨѶ¼\n");
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

	//����ʾ��ϵ�ˣ��ٰ�2��
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
	printf("������������");
	scanf("%s", myb->p[c].name);
	printf("�������Ա�1��2Ů��");
	int te;
	while (1) {
		scanf("%d", &te);
		if (te != 2 && te != 1) printf("�������������룺");
		else {
			myb->p[c].gender = te;
			break;
		}
	}
	printf("���������:");
	scanf("%s", myb->p[c].numeber);
	printf("��ɣ�");
	myb->c++;
	ffpr();//���뵽�ļ�
	system("pause");
	system("cls");
}

int  sendnum() {
	printf("��ѡ��Ҫ�Ի��˵���ţ�");
	int num = 0;
	scanf("%d", &num);
	return num;//�Խ�Ҷͩ
}

void xian(struct book* myb) {
	printf("ͨѶ¼����%d��\n", myb->c);
	int num = 0;
	for (int i = 0; i < myb->c; i++) {
		num++;
		printf("%d��", num);
		printf("%-20s", myb->p[i].name);
		myb->p[i].gender == 1 ? printf("%-20s", "��") : printf("%-20s", "Ů");
		printf("%-20s", myb->p[i].numeber);
		printf("\n");
	}
	printf("�Ƿ�����Ϣ��1���� 0����������  ѡ��");
	int choo;
	scanf("%d", &choo);
	if (choo) {
		sendnum();
	}
	else 	system("cls");
}
int ifis(char n[], struct book* myb) {
	for (int i = 0; i <= myb->c; i++) {
		if (!strcmp(myb->p[i].name, n)) { //���
			return i;
		}
	}
	return -1;//δ�ҵ�
}

void shan(struct book* myb) {
	printf("������Ҫɾ������ϵ�ˣ�");
	char temp[30];
	scanf("%s", temp);
	int ans = ifis(temp, myb);
	int c = myb->c;
	if (ans == -1) {
		printf("�����������\n");
	}
	else {
		for (int i = ans; i + 1 < c; i++) {
			myb->p[i] = myb->p[i + 1];
		}
		myb->c--;
		printf("ɾ���ɹ�");
		ffpr();
	}
	system("pause");
	system("cls");

}

void qing(struct book* myb) {
	printf("������ȷ������𣿣�������1ȷ�� 0ȡ��\n");
	int qs = 0;
	scanf("%d", &qs);
	if (qs) {
		myb->c = 0;
		FILE* fp = fopen("./ab.txt", "w");
		fprintf(fp, "%d\n", 0);
		fclose(fp);
		printf("��ɾ��\n");
	}
	else {
		printf("��ȡ����ղ���\n");
	}
	system("pause");
	system("cls");
}



int m() {
	//			printf("����������������������\n");�ò��ˣ�������
	int s = 0;
	myb.c = 0;
	ffsc();
	while (1) {
		caidan();
		printf("ѡ��");
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
			printf("����������������������\n");
			system("pause");
			system("cls");
		}
	}
}