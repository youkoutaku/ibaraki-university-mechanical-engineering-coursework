/*------------------------------------------------------------------*/
/*      		 				 <7-2b.c>							*/
/*　　　　　　　　　整数nの階乗を求めるプログラム　　　　　　　　　	*/
/*                        for文使用									*/
/*-----------------------------------------------------------------	*/
#include <stdio.h>

//関数のプロトタイプ宣言
int kaijyo(int n);

int main(void)
{
	int num;
	
	printf("整数を入力してください：");
	scanf("%d",&num);

	printf("%dの階乗は%dです\n",num,kaijyo(num));

	return 0;
}

int kaijyo(int n)
{
	int i,value=1;

	for(i=n;i>0;i--){
		value*=i;
	}
	
	return value;
}