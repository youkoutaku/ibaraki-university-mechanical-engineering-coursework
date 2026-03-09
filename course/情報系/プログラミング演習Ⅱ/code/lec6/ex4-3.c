/*------------------------------------------------------------------*/
/*      		 			　　<ex4-3.c>	　　					*/
/*　　　　構造体オブジェクトのメンバのアドレスの取り出し例　　　　　*/
/*-----------------------------------------------------------------	*/
#include <stdio.h>

//struct prog2型の宣言
struct prog2{
	int 	ID;
	char	name[20];
	int		final;
	double	mini;
	double	rpt;
};

int main(void)
{
	struct prog2 stdt1;	//struct prog2型のオブジェクトstdt1の宣言
	double score;		//総合得点用変数

	//メンバの値をキーボードからの入力
	printf("**** Input Data ****\n");
	printf("ID Number :"); 	scanf("%d", &stdt1.ID);
	printf("Name      :");	scanf("%s", stdt1.name);
	printf("Final Exam:"); 	scanf("%d", &stdt1.final);
	printf("Mini Test :"); 	scanf("%lf", &stdt1.mini);
	printf("Report    :"); 	scanf("%lf", &stdt1.rpt);

	//総合得点の計算
	score=stdt1.final+stdt1.mini+stdt1.rpt;
	
	//メンバの値と総合得点を画面に表示
	printf("**** Display Data ****\n");
    printf("ID Number :%d\n",stdt1.ID);
    printf("Name      :%s\n",stdt1.name);
	printf("Final Exam:%d\n",stdt1.final);
	printf("Mini Test :%.1f\n",stdt1.mini);
	printf("Report    :%.1f\n",stdt1.rpt);
	printf("Total Score:%.1f\n",score);

	return 0;
}
