/*------------------------------------------------------------------*/
/*      		 	<ex9-2.c>  2次元配列の動的確保①    			*/
/*　　　　　列数が定数のint型の２次元配列を動的に確保（calloc使用)  */
/*-----------------------------------------------------------------	*/
#include <stdio.h>
#include <stdlib.h>	//for exit() calloc()

int main(void)
{
	int 	i,j,	//カウンタ
			m,		//行数
			(*pt)[3];	//列数は定数（ここでは３）

	printf("行数:");
	scanf("%d",&m);

	pt=(int (*)[3])calloc(m*3, sizeof(int));	//int型をm*3個動的に確保
	if(pt==NULL){								//エラー処理
		printf("記憶領域の確保に失敗しました\n");
		exit(1);
	}
		
	for(i=0;i<m;i++)		//i,j要素に(i+1)*10+(j+1)を代入
		for(j=0;j<3;j++)	pt[i][j]=(i+1)*10+(j+1);

	for(i=0;i<m;i++){		//全要素の値を表示
		for(j=0;j<3;j++)	printf("%d ", pt[i][j]);
		printf("\n");
	}

	free(pt);	//確保していた領域の開放
	
	return 0;
}
