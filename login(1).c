#include<stdio.h>
#include<conio.h>//���ûس���ֱ������
#include<stdlib.h>//��������
void ori(char a[]) { //��ʽ�����麯������ʽ��Ϊ' '
	for (int i = 0; i < 20; i++) {
		a[i] = ' ';
	}
	a[20] = '\0';
}
//��һ���������뺯��
void input_k(char arr[]) {
	int i = 0;
	char c;
	while ((c = getch()) != '\r') {//getch�ڲ��س�������¼�¼�ַ�ֵ
		if (c != '\b') {
			printf("*");//��ʾ�Ѿ����¼��̵�ĳ���ַ�
			arr[i++] = c;
		}
		else {
			i--;//������˸���Ѽ�¼�������ʱ�����±��һ
			arr[i] = ' '; //��Ҫɾ�����ַ���Ĭ�ϵĿո����
			printf("\b \b");//ɾ������̨�ϵ�һ��*����ʾ�û�ɾ���ɹ�
		}
	}
}
void input_a(char a[]) { //�˺����뺯��
	int i = 0;
	char c;
	while ((c = getch()) != '\r') {//getch�ڲ��س�������¼�¼�ַ�ֵ
		if (c != '\b') {
			printf("%c", c); //��ʾ�Ѿ����¼��̵�ĳ���ַ�
			a[i++] = c;
		}
		else {
			i--;//������˸���Ѽ�¼�������ʱ�����±��һ
			a[i] = ' '; //��Ҫɾ�����ַ���Ĭ�ϵĿո����
			printf("\b \b");//ɾ������̨�ϵ�һ��*����ʾ�û�ɾ���ɹ�
		}
	}
}
//�ж����������Ƿ���ͬ
void compare_k(char a[], char b[]) {
	void input_k1();
	int i = 0;
	for (i = 0; a[i] != '\0'; i++) {
		if (a[i] != b[i]) {
			system("cls");
			printf("\n�ڶ��������������");
			printf("\n����������ڶ������룺");
			input_k1(a, b);//��ͬ�Ļ���������ڶ�������
		}
	}
}
//�ڶ����������뺯��
void input_k1(char a[], char b[]) {
	int i = 0;
	char c;
	while ((c = getch()) != '\r') {//getch�ڲ��س�������¼�¼�ַ�ֵ
		if (c != '\b') {
			printf("*");//��ʾ�Ѿ����¼��̵�ĳ���ַ�
			b[i++] = c;
		}
		else {
			i--;//������˸���Ѽ�¼�������ʱ�����±��һ
			b[i] = ' '; //��Ҫɾ�����ַ���Ĭ�ϵĿո����
			printf("\b \b");//ɾ������̨�ϵ�һ��*����ʾ�û�ɾ���ɹ�
		}
	}
	compare_k(a, b);
}
void Register() {
	FILE* fp, * tem_fp; //�����ļ�ָ��
	system("cls");//����
	printf("������ע���˻�\n");
	int count = 0, i = 0; //�����˺űȽ�
	char key1[21] = { '\0' }, key[21] = { '\0' }, account[21] = { '\0' }, r_account[21] = { '\0' };
	ori(key);/*��ʽ������*/
	ori(key1);
	ori(account);
	ori(r_account);
	printf("������С��15λ���˺ţ�\n");
change_k://�ڶ����������������������
	ori(account);
	input_a(account);//���벢��¼�˺�
	tem_fp = fp = fopen("./account.txt", "r");//���˻��ļ�
	while (fgetc(tem_fp) != EOF) {//�ȽϺ���ǰ��
		count = 0;
		fseek(tem_fp, -1, 1);//���ȽϺ���ǰ�ƵĻָ�
		fgets(r_account, 21, tem_fp);//��ȡ�����ʺ�
		//printf("\n%s1", r_account);
		for (i = 0; i < 20; i++) {//�������˺��������ʺ����Ա�
			if (r_account[i] != account[i]) {//����в�ͬ�ĵط�count�Ͳ�����0
				count++;
				break;
			}
		}
		if (count == 0) {//count����0˵������ͬ���˺�
			system("cls");
			printf("\n���˺��ѱ�ע���뻻һ���˺ţ�");
			goto change_k;//���ز����ù��
		}
		else
			fseek(tem_fp, 20, 1);//�����ͬ������һ���Ƿ���ͬ
	}
	fclose(fp);//��������˺ž͹ر��ļ�������������׶�
	printf("\n�˺���֤�ɹ�\n������С��20λ�����룺");
	input_k(key);//��һ����������
	printf("\n��ȷ�����룺");
	input_k1(key, key1);//�����жϺ���//�ڶ�����������
	printf("\nע��ɹ���");
	fp = fopen("./account.txt", "a");//���˻��ļ�
	fputs(account, fp);//���˺�����д���ļ�account.txt
	fputs(key, fp);
	fclose(fp);//�ر��ļ�������
}
int login(char chin_a[]) {
	char account[21], key[21], r_account[21], r_key[21];
	int count = 0, i = 0, count1 = 5;
	ori(key);/*��ʽ������*/
	ori(account);
	ori(r_account);
	ori(r_key);
	system("cls");
	printf("�����ڵ�¼\n");
change_a:
	printf("�������˺ţ�\n");
	input_a(account);//�����Լ����˺�
	FILE* fp, * tem_fp; //�����ļ�ָ��
	tem_fp = fp = fopen("./account.txt", "r");
	while (fgetc(tem_fp) != EOF) {
		count = 0;
		fseek(tem_fp, -1, 1);//���ȽϵĹ��ǰ�ƻָ�
		fgets(r_account, 21, tem_fp);//��ȡ�˺��б���˺�
		for (int i = 0; i < 20; i++) {//�Ƚ��Ƿ���ͬ
			if (r_account[i] != account[i]) {
				count++;
				break;
			}
		}
		if (count == 0) {//��Ӧ��������������
			break;
		}
		else//����Ӧ���Ƚ���һ��
			fseek(tem_fp, 20, 1);
	}
	if (count != 0) {//ȫ�Ƚ���û�ж�Ӧ��
		system("cls");
		printf("\nû�д��˺ţ����������룺");
		goto change_a;//�����������룬�����ù��
	}
	printf("\n���������룺");
change_k:
	input_k(key);//��Ӧ�˺���������
	fgets(r_key, 21, tem_fp);//��ȡ��ʵ����
	fseek(tem_fp, -20, 1);//�ָ����
	count = 0;
	for (i = 0; i < 20; i++) {//�Ƚ����������ʵ��
		if (r_key[i] != key[i]) {
			count++;
			break;
		}
	}
	if (count == 0) {//countΪ0����û�в�ͬ��
		printf("\n��¼�ɹ���");
		i = 0;
		while ((int)account[i] != 32 && i < 20) {
			chin_a[i] = account[i];
			i++;
		}
	}
	else {//���������
		count1--;//ʣ�������һ
		if (count1 == 0) {
			fclose(fp);
			return 1;//û�д������˳���������һ���˳�������
		}
		if (count1 < 4) {//ʣ�����
			printf("\n������%d�λ��ᣡ", count1);
		}
		printf("\n����������������룺");//���󷵻���������
		goto change_k;
	}
	fclose(fp);//�ر��ļ�
	return 0;//�رյ�¼������������
}
void login_register(char l_account[]) {
	ori(l_account);
return1:
	system("cls");
	printf("\n���Ƿ�ӵ���˻�\n0)��  1)û��\n���������֣�");
	int x = 1; //�Ƿ����˺ŵ�ѡ��
	scanf("%d", &x);
	if (x==1) {//û�У�ע��
		Register();
		goto return1;
	}
	else {//�У���¼
		if (login(l_account))
			goto return1;	//������������˳�
	}
}
//int main(){
//  char l_account[21];
//  ori(l_account);
//  login_register(l_account);
//  printf("%s",l_account);
//  }