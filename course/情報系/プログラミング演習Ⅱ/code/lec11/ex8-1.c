//     <ex8-1.c>
//ポインタ変数がオブジェクトのアドレスを代入する変数であることを
//確認するプログラム

#include <stdio.h>

int main(void)
{
	int x=100;
	int *p;

	p=&x;
	
	printf("xのアドレス    ：%p\n",&x);
	printf("xの値          ：%d\n",x);

	printf("pのアドレス　　：%p\n",&p);
	printf("pが指すアドレス：%p\n",p);
	printf("pが指すアドレスに格納されている値：%d\n",*p);

	return 0;
}