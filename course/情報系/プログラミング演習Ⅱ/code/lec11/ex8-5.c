/*------------------------------------------------------------------*/
/*      		 			<ex8-5.c>			  	    			*/
/*　　　　　　　　　２次元配列の間数間の受け渡し　　　　　　　　　　*/
/*-----------------------------------------------------------------	*/
#include <stdio.h>

//関数のプロトタイプ宣言
void print_data(char (*x)[7]);

int main(void)
{
	char 	a[3][7]={"red","blue", "yellow"}; 	//２次元配列の宣言と初期化

	print_data(a);

	return 0;
}

void print_data(char (*x)[7])
{
	int 	i;
	
	for(i=0;i<3;i++) printf("a[%d]=%s\n",i,x[i]);
}
