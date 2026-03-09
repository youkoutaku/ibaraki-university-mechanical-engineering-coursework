//得点0～100のデータ 
//まず、０～１０１の行列(juni[100+2])を宣言し、初期化する
//次に101行列に1を入れる。他に値があるところに1+
//そして、100~0の各行列に、一つ右の要素を加えていく
//最後、nの順位はn+1行列の値である。
#include <stdio.h>

#define Num 10
#define Max 100
#define Min 0

int main (void){
    int a[] = {56, 25, 67, 88, 100, 61, 55, 67, 76, 56};
    int i, juni[Max+2];

    for(i=Min; i<=Max; i++){
        juni[i]=0;
    }
    for(i=0; i<=Num; i++){
        juni[a[i]]++;
    }
    juni[Max+1]=1;
    for(i=Max; i>=Min; i--){
        juni[i]+=juni[i+1];
    }
    printf(" 得点　順位\n");
    for (i=0; i<Num; i++){
        printf("%6d%6d\n", a[i], juni[a[i]+1]);
    }
    return 0;
}