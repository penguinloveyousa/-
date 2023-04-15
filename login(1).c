#include<stdio.h>
#include<conio.h>//不用回车键直接输入
#include<stdlib.h>//清屏函数
void ori(char a[]) { //格式化数组函数，格式化为' '
	for (int i = 0; i < 20; i++) {
		a[i] = ' ';
	}
	a[20] = '\0';
}
//第一次密码输入函数
void input_k(char arr[]) {
	int i = 0;
	char c;
	while ((c = getch()) != '\r') {//getch在不回车的情况下记录字符值
		if (c != '\b') {
			printf("*");//提示已经按下键盘的某个字符
			arr[i++] = c;
		}
		else {
			i--;//如果按退格键把记录密码的临时数组下标减一
			arr[i] = ' '; //把要删除的字符用默认的空格代替
			printf("\b \b");//删除控制台上的一个*，提示用户删除成功
		}
	}
}
void input_a(char a[]) { //账号输入函数
	int i = 0;
	char c;
	while ((c = getch()) != '\r') {//getch在不回车的情况下记录字符值
		if (c != '\b') {
			printf("%c", c); //提示已经按下键盘的某个字符
			a[i++] = c;
		}
		else {
			i--;//如果按退格键把记录密码的临时数组下标减一
			a[i] = ' '; //把要删除的字符用默认的空格代替
			printf("\b \b");//删除控制台上的一个*，提示用户删除成功
		}
	}
}
//判断俩次密码是否相同
void compare_k(char a[], char b[]) {
	void input_k1();
	int i = 0;
	for (i = 0; a[i] != '\0'; i++) {
		if (a[i] != b[i]) {
			system("cls");
			printf("\n第二次输入密码错误");
			printf("\n请重新输入第二次密码：");
			input_k1(a, b);//不同的话重新输入第二次密码
		}
	}
}
//第二次密码输入函数
void input_k1(char a[], char b[]) {
	int i = 0;
	char c;
	while ((c = getch()) != '\r') {//getch在不回车的情况下记录字符值
		if (c != '\b') {
			printf("*");//提示已经按下键盘的某个字符
			b[i++] = c;
		}
		else {
			i--;//如果按退格键把记录密码的临时数组下标减一
			b[i] = ' '; //把要删除的字符用默认的空格代替
			printf("\b \b");//删除控制台上的一个*，提示用户删除成功
		}
	}
	compare_k(a, b);
}
void Register() {
	FILE* fp, * tem_fp; //创建文件指针
	system("cls");//清屏
	printf("您正在注册账户\n");
	int count = 0, i = 0; //用于账号比较
	char key1[21] = { '\0' }, key[21] = { '\0' }, account[21] = { '\0' }, r_account[21] = { '\0' };
	ori(key);/*格式化数组*/
	ori(key1);
	ori(account);
	ori(r_account);
	printf("请输入小于15位的账号：\n");
change_k://第二次密码输入错误重新输入
	ori(account);
	input_a(account);//输入并记录账号
	tem_fp = fp = fopen("./account.txt", "r");//打开账户文件
	while (fgetc(tem_fp) != EOF) {//比较后光标前移
		count = 0;
		fseek(tem_fp, -1, 1);//将比较后光标前移的恢复
		fgets(r_account, 21, tem_fp);//读取已有帐号
		//printf("\n%s1", r_account);
		for (i = 0; i < 20; i++) {//将输入账号与已有帐号做对比
			if (r_account[i] != account[i]) {//如果有不同的地方count就不等于0
				count++;
				break;
			}
		}
		if (count == 0) {//count等于0说明有相同的账号
			system("cls");
			printf("\n该账号已被注册请换一个账号：");
			goto change_k;//返回并重置光标
		}
		else
			fseek(tem_fp, 20, 1);//如果不同查找下一个是否相同
	}
	fclose(fp);//如果是新账号就关闭文件进入设置密码阶段
	printf("\n账号验证成功\n请输入小于20位的密码：");
	input_k(key);//第一次输入密码
	printf("\n请确认密码：");
	input_k1(key, key1);//包含判断函数//第二次输入密码
	printf("\n注册成功！");
	fp = fopen("./account.txt", "a");//打开账户文件
	fputs(account, fp);//将账号密码写入文件account.txt
	fputs(key, fp);
	fclose(fp);//关闭文件并保存
}
int login(char chin_a[]) {
	char account[21], key[21], r_account[21], r_key[21];
	int count = 0, i = 0, count1 = 5;
	ori(key);/*格式化数组*/
	ori(account);
	ori(r_account);
	ori(r_key);
	system("cls");
	printf("您正在登录\n");
change_a:
	printf("请输入账号：\n");
	input_a(account);//输入自己的账号
	FILE* fp, * tem_fp; //创建文件指针
	tem_fp = fp = fopen("./account.txt", "r");
	while (fgetc(tem_fp) != EOF) {
		count = 0;
		fseek(tem_fp, -1, 1);//将比较的光标前移恢复
		fgets(r_account, 21, tem_fp);//读取账号列表的账号
		for (int i = 0; i < 20; i++) {//比较是否相同
			if (r_account[i] != account[i]) {
				count++;
				break;
			}
		}
		if (count == 0) {//对应，继续输入密码
			break;
		}
		else//不对应，比较下一个
			fseek(tem_fp, 20, 1);
	}
	if (count != 0) {//全比较完没有对应的
		system("cls");
		printf("\n没有此账号，请重新输入：");
		goto change_a;//返回重新输入，并重置光标
	}
	printf("\n请输入密码：");
change_k:
	input_k(key);//对应账号输入密码
	fgets(r_key, 21, tem_fp);//读取真实密码
	fseek(tem_fp, -20, 1);//恢复光标
	count = 0;
	for (i = 0; i < 20; i++) {//比较输入的与真实的
		if (r_key[i] != key[i]) {
			count++;
			break;
		}
	}
	if (count == 0) {//count为0代表没有不同的
		printf("\n登录成功！");
		i = 0;
		while ((int)account[i] != 32 && i < 20) {
			chin_a[i] = account[i];
			i++;
		}
	}
	else {//密码错误则
		count1--;//剩余次数减一
		if (count1 == 0) {
			fclose(fp);
			return 1;//没有次数就退出函数，进一步退出主函数
		}
		if (count1 < 4) {//剩余次数
			printf("\n您还有%d次机会！", count1);
		}
		printf("\n密码错误！请重新输入：");//错误返回重新输入
		goto change_k;
	}
	fclose(fp);//关闭文件
	return 0;//关闭登录函数继续操作
}
void login_register(char l_account[]) {
	ori(l_account);
return1:
	system("cls");
	printf("\n您是否拥有账户\n0)有  1)没有\n请输入数字：");
	int x = 1; //是否有账号的选择
	scanf("%d", &x);
	if (x==1) {//没有，注册
		Register();
		goto return1;
	}
	else {//有，登录
		if (login(l_account))
			goto return1;	//密码持续错误退出
	}
}
//int main(){
//  char l_account[21];
//  ori(l_account);
//  login_register(l_account);
//  printf("%s",l_account);
//  }