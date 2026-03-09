/*------------------------------------------------------------------*/
/*      		 			　　<ex5-3.c>	　　					*/
/*　    構造体変数を引数にとる関数の例（ポインタ渡し、戻り値なし）  */
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

//関数のプロトタイプ宣言
void TotalScore2(Prog2 *obj);

int main(void)
{
	//Prog2型のオブジェクトの宣言と初期化
	Prog2 stdt1={251001,"sasaki", 40,30,30};
	
	TotalScore2(&stdt1);	//総合得点の計算と表示
		
	return 0;
}

void TotalScore2(Prog2 *obj)
{
	double score;

	score=obj->final+obj->mini+obj->rpt;

	printf("%d %s %.1f\n",obj->ID, obj->name, score);
}