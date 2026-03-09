/*------------------------------------------------------------------*/
/*      		 			  <ex7-3.c>							    */
/*　　　　　　　　　　　　　　ハノイの塔　　　　　　　　　　　　　	*/
/*-----------------------------------------------------------------	*/
#include <stdio.h>

//関数のプロトタイプ宣言
void hanoi(int n,int a, int b, int c);

int main(void)
{
	int num;
	
	printf("円盤の数を入力してください：");
	scanf("%d",&num);

	hanoi(num,'a','b','c');

	return 0;
}

void hanoi(int n, int a, int b, int c)
{
	if(n==1)					//nが1の場合
		printf("%dの円盤を %c から %c に移す\n",n,a,b);	//
	else{						//nが１でない場合
		hanoi(n-1,a,c,b);		//n-1枚の円盤をaからcにハノイ移し
		printf("%dの円盤を %c から %c に移す\n",n,a,b);
		hanoi(n-1,c,b,a);		//n-1枚の円盤をcからbにハノイ移し
	}
}