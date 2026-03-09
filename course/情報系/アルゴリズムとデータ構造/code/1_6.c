//   ユークリッドの互除法
//(m-n)の代わりに剰余（ｍ％ｎ）を用いる

#include <stdio.h>

int main (void){
    int a, b, m, n, k;

    printf("二つの整数を入力してください");
    scanf("%d %d", &a, &b);

    m=a; n=b;
    do{
        k=m % n;
        m=n; n=k;
    }while(k!=0);
    printf("最大公約数= %d\n", m);

    return 0;
}
