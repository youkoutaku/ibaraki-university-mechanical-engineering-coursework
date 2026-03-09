/*------------------------------------------------------------------*/
/*      		 			　　<ex6-3.c>	　　					*/
/*	入れ子構造の構造体オブジェクトのアドレス取り出しのプログラム例　*/
/*　　　　　　　　　 （構造体変数を返す関数） 　　　　　　　        */
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

//関数のプロトタイプ宣言
Prog2 input_data(void);

int main(void)
{
	Prog2 stdt1;	//Prog2型のオブジェクトstdt1の宣言
	
	stdt1=input_data();
	
	//メンバの値を画面に表示
	printf("**** Input Data ****\n");
    printf("ID Number :%d\n", stdt1.ID);
	printf("Name      :%s\n", stdt1.name);
	printf("Final Exam:%d\n", stdt1.sc.final);
	printf("Mini Test :%.1f\n", stdt1.sc.mini);
	printf("Report    :%.1f\n", stdt1.sc.rpt);

	return 0;
}

Prog2 input_data(void)
{
	Prog2 obj;

	//メンバの値をキーボードからの入力
	printf("**** Diplay Data ****\n");
	printf("ID Number :"); 	scanf("%d", &obj.ID);
	printf("Name      :"); 	scanf("%s", obj.name);
	printf("Final Exam:"); 	scanf("%d", &obj.sc.final);
	printf("Mini Test :"); 	scanf("%lf", &obj.sc.mini);
	printf("Report    :"); 	scanf("%lf", &obj.sc.rpt);

	return obj;
}
