/*------------------------------------------------------------------*/
/*      		 			　<ex13-1.c> 					　　    */
/*             staticの付いたローカル変数を使用したプログラム例		*/
/*------------------------------------------------------------------*/
#include <stdio.h>

int deposit(int mput);

int main(void)
{
	int money;
	
	do{
		printf("How much do you want to deposit?:"); scanf("%d", &money);
		printf("The saving amount is %d yen.\n", deposit(money));
	}while(money!=0);

	return 0;
}

int deposit(int mput)
{
	static int value=0;	//貯金額（静的変数：初期化は最初の呼び出しのときだけ）

	value+=mput;
	return value;
}

