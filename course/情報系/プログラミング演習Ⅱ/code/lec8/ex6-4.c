/*------------------------------------------------------------------*/
/*      		 			　　<ex6-4.c>	　　					*/
/*　入れ子構造の構造体の配列の宣言・初期化・参照のプログラム例　　　*/
/*-----------------------------------------------------------------	*/
#include <stdio.h>
#define SNUM 5

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

//関数のプロトタイプ宣言
void print_data(Prog2 *obj);

int main(void)
{
	//Prog2型の配列Mech[SNUM]の宣言と初期化
	Prog2 Mech[SNUM]={		
				{251001,"sasaki",{40,30,30}},	//Mech[0]の初期化子
				{251002,"sato",{35,25,25}},		//Mech[1]の初期化子
				{251003,"kato",{30,20,20}},		//Mech[2]の初期化子
	};
	
	print_data(Mech);	//総合得点の計算と表示
	
	return 0;
}

void print_data(Prog2 *obj)
{
	int	i;			//カウンタ
	double 	score;	//総合得点用変数

	//学生番号、項目別得点、総合得点の表示
	printf("%-10s%-10s%10s%10s%10s%10s\n", 
      "ID","Name","Mini","Report","Final","Total");
	for(i=0;i<SNUM;i++){
		score=obj[i].sc.final+obj[i].sc.mini+obj[i].sc.rpt;
		printf("%-10d%-10s%10.1f%10.1f%10d%10.1f\n", obj[i].ID,
				obj[i].name, obj[i].sc.mini, obj[i].sc.rpt,
				obj[i].sc.final, score);
	}
}
