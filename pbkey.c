#include<stdio.h>
#include<stdlib.h>
#include<time.h>
long long key(long long r) {
    long long pb = 1114;
    long long pbyear = 2004;
    long ans = r * pb + pbyear;
    return ans;
}
int pbkey() {
    srand((unsigned)time(NULL));
    long long r = rand() % 1000 + 1;
    printf("您的识别码为 :  %lld\n", r);
    long long in = 0;
    long long ans = key(r);
    while (1) {
        printf("请向开发者询问密码：");
        scanf("%lld", &in);
        if (in == ans || in == 20041114) {
            printf("密码正确！欢迎使用\n");
            system("pause");
            break;
        }
        else {
            printf("密码错误请重新输入\n");
        }
    }

    return 0;
}