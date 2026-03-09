/*------------------------------------------------------------------*/
/*      		 			　　<ex6-1.c>	　　					*/
/*　      入れ子構造の構造体オブジェクトの初期化のプログラム例　    */
/*-----------------------------------------------------------------	*/
#include <stdio.h>

//Seiseki型の宣言
typedef struct{
	int		final;
	double	mini;
	double	rpt;
} Seiseki;

//Prog2型の宣言
typedef struct {
	int		ID;
	char	name[20];
	Seiseki	sc;
} Prog2;

int main(void)
{
	//Prog2型のオブジェクトの宣言と初期化
	Prog2 stdt1={251001,"sasaki",{40,30,30}};
	
	//メンバの値を画面に表示
	printf("ID Number :%d\n", stdt1.ID);
	printf("Name      :%s\n", stdt1.name);
	printf("Final Exam:%d\n", stdt1.sc.final);
	printf("Mini Test :%.1f\n", stdt1.sc.mini);
	printf("Report    :%.1f\n", stdt1.sc.rpt);
	
	return 0;
}