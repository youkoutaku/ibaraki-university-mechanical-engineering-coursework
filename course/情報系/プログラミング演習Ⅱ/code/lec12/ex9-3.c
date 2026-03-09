/*------------------------------------------------------------------*/
/*      		<ex9-3.c> 2次元配列の動的確保②	  	    			*/
/*　　　　行数と列数が可変の２次元配列を動的に確保（calloc使用)　　 */
/*-----------------------------------------------------------------	*/
#include <stdio.h>
#include <stdlib.h>	//for exit() calloc()

void Matrix_free(int **p, int num);

int main(void)
{
	int 	i,j,	//カウンタ
			m,		//行数
			n,		//列数
			**pt;   //ポインタへのポインタ

	printf("行数:");	scanf("%d",&m);
	printf("列数:");	scanf("%d",&n);

	pt=(int **)calloc(m, sizeof(int *));//要素数がmのint型へのポインタ配列の確保
	if(pt==NULL){					//エラー処理
		printf("記憶領域の確保に失敗しました\n");
		exit(1);
	}

	for(i=0;i<m;i++)	pt[i]=NULL;	//ポインタ配列ptの全要素にNULLを代入
		
	for(i=0;i<m;i++){
		pt[i]=(int *)calloc(n,sizeof(int)); //要素数がnのint型の配列を確保し，確保した配列へのポインタを pt[i] に代入
		if(pt[i]==NULL){
			printf("記憶領域の確保に失敗しました\n");
			exit(0);
		}
	}

	for(i=0;i<m;i++)		//i,j要素に(i+1)*10+(j+1)を代入
		for(j=0;j<n;j++)	pt[i][j]=(i+1)*10+(j+1);			          

	for(i=0;i<m;i++){		//全要素の値を表示
		for(j=0;j<n;j++)	printf("%d ",pt[i][j]);
		printf("\n");
	}

	Matrix_free(pt,m);		//確保していた領域の開放
	
	return 0;
}

//確保した全領域の開放
void Matrix_free(int **p, int num)
{
	int i;
	
	for(i=0;i<num;i++)	free(p[i]);
	free(p);
}
