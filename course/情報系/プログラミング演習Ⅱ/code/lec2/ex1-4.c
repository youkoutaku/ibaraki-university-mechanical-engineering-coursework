/*------------------------------------------------------------------*/
/*      		 			　<ex1-4.c>	(タブ4）				    */
/*　　　　　　プログラミング演習Ⅱの成績の計算＆表示     　　　　　	*/
/*-----------------------------------------------------------------	*/
#include <stdio.h>

int main(void)
{
	int		ID,		//学生番号
			final,	//期末試験
			retry;	//繰り返し判定(0:実行しない 1:実行)
	double	mini,	//小テスト
			rpt,	//レポート
			score;  //総合得点

	do{
		//学生番号と項目別得点の入力
		printf("ID Number :");	scanf("%d",&ID);
		printf("Mini Test :");	scanf("%lf",&mini);
		printf("Report    :");	scanf("%lf",&rpt);
		printf("Final Exam:");	scanf("%d",&final);
	
		score=mini+rpt+final;	//総合得点の計算

		//データラベルの表示
    	printf("%-8s%10s%10s\n", "ID NUMBER","SCORE","GRADE");
	
		//学生番号、総合得点の表示
		printf("%-8d%10.1f",ID,score);

		//成績判定（A+～D)と表示
		if(score>=90)	printf("%10s\n","A+");
		else if(score>=80) printf("%10s\n","A");
		else if(score>=70) printf("%10s\n","B");
		else if(score>=60) printf("%10s\n","C");
		else	printf("%10s\n","D");
		printf("繰り返しますか？0-いいえ/1-はい:");
		scanf("%d", &retry);

	}while(retry==1);	//retryが１の間は実行を繰り返す
	
	return 0;
}
