/*------------------------------------------------------------------*/
/*      		 			 <ex9-1.c>			  	    			*/
/*　　　　　　int型の一次元配列を動的に確保              　　　　　 */
/*-----------------------------------------------------------------	*/
#include <stdio.h>
#include <stdlib.h>	//for exit() calloc()

int main(void)
{
	int 	i,			//カウンタ
			num,		//配列の要素数
			*pm, *pc;   //確保する領域を指すためのポインタ

	printf("確保する配列の要素数:");
	scanf("%d",&num);

	pc=(int *)calloc(num, sizeof(int));	//int型をnum個動的に確保
	if(pc==NULL){						//エラー処理
		printf("配列pcの領域の確保に失敗しました\n");
		exit(1);
	}
	
	pm=(int *)malloc(num*sizeof(int));	//int型をnum個動的に確保
	if(pm==NULL){						//エラー処理
		printf("配列pmの領域の確保に失敗しました\n");
		exit(1);
	}
	
	for(i=0;i<num;i++)	printf("pc[%d]=%d\n",i,pc[i]);//配列pcの全要素の値を表示
	for(i=0;i<num;i++)	printf("pm[%d]=%d\n",i,pm[i]);//配列pmの全要素の値を表示

	free(pc);		//配列pc用に確保していた領域の開放
	free(pm);		//配列pm用に確保していた領域の開放
	
	return 0;
}
