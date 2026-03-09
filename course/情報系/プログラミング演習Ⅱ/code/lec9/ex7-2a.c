/*------------------------------------------------------------------*/
/*      		 				 <ex7-2a.c>							*/
/*　　　　　　　整数nの階乗を求めるプログラム（再帰コール）　　　　	*/
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
	if(n==1)					//nが1の場合
		return 1;				//1を返す
	else						//nが１でない場合
		return n*kaijyo(n-1);	//n*(n-1)の階乗を返す
}
