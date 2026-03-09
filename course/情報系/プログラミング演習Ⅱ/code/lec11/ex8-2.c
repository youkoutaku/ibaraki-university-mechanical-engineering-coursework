/*------------------------------------------------------------------*/
/*      		 			<ex8-2.c>			  	    			*/
/*　　　　　　　　　 　　1次元配列とポインタ   　　　　　　　　　　 */
/*-----------------------------------------------------------------	*/
#include <stdio.h>

int main(void)
{
	int 	i;

	//一次元配列の宣言と初期化
	char 	a[4]="red"; 
	int		b[4]={100,101,102,103};
	double	c[4]={0.00,0.01,0.02,0.03};
		
	//ポインタ変数を宣言し、1次元配列先頭アドレスを代入
	char	*pa=a;
	int		*pb=b;
	double	*pc=c;

	//char型、int型、double型のバイト数表示
	printf("sizeof(char)=%d\n", sizeof(char));
	printf("sizeof(int)=%d\n", sizeof(int));
	printf("sizeof(double)=%d\n", sizeof(double));
	printf("-----------------------------\n");

	for(i=0;i<4;i++)	//pa+iのアドレスと*(pa+i)を出力
		printf("pa+%d=%p \t *(pa+%d)=%c\n",i,pa+i,i,*(pa+i));
	printf("-----------------------------\n");

	for(i=0;i<4;i++)	//pb+iのアドレスと*(pb+i)を出力
		printf("pb+%d=%p \t *(pb+%d)=%d\n",i,pb+i,i,*(pb+i));
	printf("-----------------------------\n");
		
	for(i=0;i<4;i++)	//pc+iのアドレスと*(pc+i)を出力
		printf("pc+%d=%p \t *(pc+%d)=%.2f\n",i,pc+i,i,*(pc+i));


	return 0;
}
