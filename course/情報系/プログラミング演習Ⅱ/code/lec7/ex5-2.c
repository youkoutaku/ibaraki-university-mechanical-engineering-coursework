/*------------------------------------------------------------------*/
/*      		 			　　<ex5-2.c>	　　					*/
/*　      構造体変数を引数にとる関数の例（値渡し、戻り値なし）　    */
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
void TotalScore1(Prog2 obj);

int main(void)
{
	//Prog2型のオブジェクトの宣言と初期化
	Prog2 stdt1={2510001,"sasaki",40,30,30};
	
	TotalScore1(stdt1);	//関数TotalScore1の呼び出し
		
	return 0;
}

void TotalScore1(Prog2 obj)
{
	double score;

	score=obj.final+obj.mini+obj.rpt;	//総合得点の計算

	printf("%d %s %.1f\n",obj.ID, obj.name, score);		//総合得点の表示

}