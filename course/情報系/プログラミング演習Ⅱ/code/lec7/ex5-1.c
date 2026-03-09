/*------------------------------------------------------------------*/
/*      		 			　　<ex5-1.c>	　　					*/
/*　　　　　　　　構造体オブジェクトへのポインタの使用例　　　　　　*/
/*-----------------------------------------------------------------	*/
#include <stdio.h>

//Prog2型の宣言
typedef struct {
	int		ID;
	char	name[20];
	int		final;
	double	mini;
	double	rpt;
} Prog2;


int main(void)
{
	//Prog2型のオブジェクトの宣言と初期化
	Prog2 stdt1={251001,"sasaki",40,30,30};
	Prog2 *pt=&stdt1;
	
	printf("ID Number :%d\n",pt->ID);
	printf("Name      :%s\n",pt->name);
	printf("Final Exam:%d\n",pt->final);
	printf("Mini Test :%.1f\n",pt->mini);
	printf("Report    :%.1f\n",pt->rpt);
	
	return 0;
}