/*------------------------------------------------------------------*/
/*      		 			　　<ex4-2.c>	　　					*/
/*				構造体オブジェクトの初期化のプログラム例　　　　	*/
/*-----------------------------------------------------------------	*/
#include <stdio.h>

//struct prog2型の宣言
struct prog2{
	int 	ID;			//学生番号
	char	name[20];	//名前
	int		final;		//期末試験得点
	double	mini;		//小テスト得点
	double	rpt;		//レポート得点
};

int main(void)
{
	//struct prog2型のオブジェクトstdt1の宣言と初期化
	struct prog2 stdt1={251001,"sasaki",40,30,30};
	double score;		//総合得点用変数
	
	printf("ID Number :%d\n", stdt1.ID);
	printf("Name      :%s\n", stdt1.name);
	printf("Final Exam:%d\n", stdt1.final);
	printf("Mini Test :%.1f\n", stdt1.mini);
	printf("Report    :%.1f\n", stdt1.rpt);
	
	//総合得点の計算
	score=stdt1.final+stdt1.mini+stdt1.rpt;
	
	printf("Total Score:%.1f\n",score);

	return 0;
}
