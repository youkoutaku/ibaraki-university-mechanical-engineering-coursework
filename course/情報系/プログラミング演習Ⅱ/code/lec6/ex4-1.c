/*------------------------------------------------------------------*/
/*      		 			　　<ex4-1.c>	　　					*/
/*構造体の宣言とオブジェクトの使用宣言およびメンバ参照のプログラム　*/
/*-----------------------------------------------------------------	*/
#include <stdio.h>
#include <string.h>

//struct prog2型の宣言
struct prog2{
	int 	ID;			//学生番号
	char    name[20];	//名前
	int		final;		//期末試験得点
	double	mini;		//小テスト得点
	double	rpt;		//レポート得点
};

int main(void)
{
	struct prog2 stdt1;				//struct prog2型のオブジェクトstdt1の宣言
	double score;					//総合得点用変数
	
	stdt1.ID=251001;				//学生番号の代入
	strcpy(stdt1.name, "sasaki"); 	/* 文字列"sasaki"を変数stdt1のメンバの
                                       配列nameにコピー */
	stdt1.final=40;					//期末試験の得点の代入
	stdt1.mini=30;					//小テストの得点の代入
	stdt1.rpt=30;					//レポートの得点の代入

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
