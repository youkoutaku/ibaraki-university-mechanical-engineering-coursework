/*------------------------------------------------------------------*/
/*      		 			　　<ex5-4.c>	　　					*/
/*　　　　　　　　　構造体変数を返す関数の例　　　　　　　　        */
/*-----------------------------------------------------------------	*/
#include <stdio.h>

//Prog2型の宣言
typedef struct{
	int 	ID;
	char	name[20];
	int		final;
	double	mini;
	double	rpt;
} Prog2;

//関数のプロトタイプ宣言
Prog2 input_data(void);

int main(void)
{
	Prog2 stdt1;	//Prog2型のオブジェクトstdt1の宣言
	
	stdt1=input_data();
	
	//メンバの値を画面に表示
	printf("**** Display Data ****\n");
	printf("ID Number :%d\n",stdt1.ID);
	printf("Name      :%s\n",stdt1.name);
	printf("Final Exam:%d\n",stdt1.final);
	printf("Mini Test :%.1f\n",stdt1.mini);
	printf("Report    :%.1f\n",stdt1.rpt);

	return 0;
}

Prog2 input_data(void)
{
	Prog2 obj;

	//メンバの値をキーボードからの入力
	printf("**** Input Data ****\n");
	printf("ID Number :"); 	scanf("%d",&obj.ID);
	printf("Name      :"); 	scanf("%s",obj.name);
	printf("Final Exam:"); 	scanf("%d",&obj.final);
	printf("Mini Test :"); 	scanf("%lf",&obj.mini);
	printf("Report    :"); 	scanf("%lf",&obj.rpt);

	return obj;
}
