/*------------------------------------------------------------------*/
/*      		 		  	  <ex11-2.c>	  		  				*/
/*　　　　　　　関数形式マクロの例(#演算子と##演算子）　　　　　　　*/
/*                       　　　　　　　　　　　　　　　　　　　　　 */
/*-----------------------------------------------------------------	*/
#include <stdio.h>

#define mctst0(dt) "引数はdtです"
#define mctst1(dt) "引数は" #dt "です"

#define mctst2(dt) my##dt##size

#define dataout(dt) printf(#dt "=%d\n",dt)

int main(void)
{
	int dt=1,sum=0,ary[3]={10,20,30};
	int myHsize=170,myFsize=25;

	// #演算子-引数の文字列化
	printf(mctst0(aaa)); printf("\n");
	printf(mctst1(aaa)); printf("\n");

	dataout(sum);
	dataout(ary[0]);
	dataout(dt+10);

	// ##演算子-トークンの結合
	dataout(mctst2(H));
	dataout(mctst2(F));

	return 0;
}