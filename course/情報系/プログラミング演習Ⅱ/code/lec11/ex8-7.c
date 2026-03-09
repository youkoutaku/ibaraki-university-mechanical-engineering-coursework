/*------------------------------------------------------------------*/
/*      		 			<ex8-7.c>			  	    			*/
/*　　　　　　  関数間でのポインタ配列の受け渡し　　　　　　　　　　*/
/*-----------------------------------------------------------------	*/
#include <stdio.h>

//関数のプロトタイプ宣言
void print_data(char **c);

int main(void)
{
	char 	*b[3]={"red","blue", "yellow"}; //ポインタ配列の宣言と初期化

	print_data(b);
	
	return 0;
}

void print_data(char **x)
{
	int i;
	
	for(i=0;i<3;i++) printf("b[%d]=%s\n",i,x[i]);
}
