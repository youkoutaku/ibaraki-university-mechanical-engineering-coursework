/*------------------------------------------------------------------*/
/*      		  <ex9-5.c> 2次元配列の動的確保④  	    		*/
/*　　1次元配列を動的に確保して、2次元配列として扱う（calloc使用)　 */
/*-----------------------------------------------------------------	*/
#include <stdio.h>
#include <stdlib.h>	//for exit() calloc()

int main(void)
{
	int 	i,j,	//カウンタ
			m,		//行数
			n,		//列数
			*p;   	//ポインタ

	printf("行数:");	scanf("%d",&m);
	printf("列数:");	scanf("%d",&n);

	p=(int *)calloc(m*n, sizeof(int));	//int型をm*n個確保
	if(p==NULL){					//エラー処理
		printf("記憶領域の確保に失敗しました\n");
		exit(1);
	}

	for(i=0;i<m;i++)			//i,j要素に(i+1)*10+(j+1)を代入
		for(j=0;j<n;j++)	p[i*n+j]=(i+1)*10+(j+1);			          

	for(i=0;i<m;i++){			//全要素の値を表示
		for(j=0;j<n;j++)	printf("%d ",p[i*n+j]);
		printf("\n");
	}

	free(p);		//確保していた領域の開放
	
	return 0;
}