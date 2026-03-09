/*------------------------------------------------------------------*/
/*      		 			 <ex9-4.c>			  	    			*/
/*                     2次元配列の動的確保③　　　　　　　　　　　　*/
/*　　　　　行によって列の大きさの違う2次元配列を動的に確保 　　　　*/
/*                         （calloc使用)  　                        */
/*-----------------------------------------------------------------	*/
#include <stdio.h>
#include <stdlib.h>	//for exit() calloc()
#include <string.h>

void Matrix_free(char **p, int num);

int main(void)
{
	int 	i,	//カウンタ
			n;	//文字数
	char	**c,
			buf[80];

	printf("文字列数:");	scanf("%d",&n);

	c=(char **)calloc(n, sizeof(char *));//char型への要素数nのポインタ配列を確保
	if(c==NULL){								//エラー処理
		printf("記憶領域の確保に失敗しました\n");
		exit(1);
	}

	for(i=0;i<n;i++)	c[i]=NULL;		//ポインタ配列cの全要素にNULLを代入
		
	for(i=0;i<n;i++){
		printf("文字列%d:",i+1);	scanf("%s",buf);
		c[i]=(char *)calloc(strlen(buf)+1,sizeof(char));
		if(c[i]==NULL){
			printf("文字列%dの記憶領域の確保に失敗しました\n", i+1);
			exit(0);
		}
		strcpy(c[i],buf);
	}

	for(i=0;i<n;i++)					//全要素の値を表示
		printf("c[%d]=%s\n",i,c[i]);	

	Matrix_free(c,n);					//確保していた領域の開放
	
	return 0;
}

//確保した全領域の開放
void Matrix_free(char **p, int num)
{
	int i;
	
	for(i=0;i<num;i++)	free(p[i]);
	free(p);
}
