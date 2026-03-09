/*------------------------------------------------------------------*/
/*      		 			　　<ex4-4.c>	　　					*/
/*　　　　　構造体の配列の宣言・初期化・参照のプログラム例　　　　　*/
/*-----------------------------------------------------------------	*/
#include <stdio.h>
#define SNUM 5

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
	int		i;			//カウンタ
	double 	score;		//総合得点用変数
	//struct prog2型の配列prog2[SNUM]の宣言と初期化
	struct prog2 Mech[SNUM]={		
				{251001, "sasaki", 40, 30, 30},	//Mech[0]の初期化子
				{251002, "kato", 35, 25 ,25},	//Mech[1]の初期化子
				{251003, "sato", 30, 20, 20},	//Mech[2]の初期化子
	};
	
	//学生番号、項目別得点、総合得点の表示
	printf("%-10s%-10s%10s%10s%10s%10s\n", 
      "ID","Name","Mini","Report","Final","Total");

	for(i=0;i<SNUM;i++){
		score=Mech[i].final+Mech[i].mini+Mech[i].rpt;
	   	printf("%-10d%-10s%10.1f%10.1f%10d%10.1f\n", Mech[i].ID,
        	Mech[i].name, Mech[i].mini, Mech[i].rpt, Mech[i].final,score);
	}

	return 0;
}
