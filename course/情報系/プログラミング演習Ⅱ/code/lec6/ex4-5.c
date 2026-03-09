/*------------------------------------------------------------------*/
/*      		 			　　<ex4-5.c>	　　					*/
/*　　　　　構造体の配列のメンバのアドレス参照のプログラム例　　　　*/
/*          ファイルから得点データを読み込み、成績評価と共に        */
/*          画面に出力する　　　　　　                              */
/* （注意）エディタのタブの文字数を「４」に設定するとずれません     */
/*-----------------------------------------------------------------	*/
#include <stdio.h>
#include <stdlib.h> //for exit()
#include <string.h>
#define SNUM 5

//struct prog2型の宣言
struct prog2{
	int 	ID;			//学生番号
	char    name[20];	//名前
	int		final;		//期末試験得点
	double	mini;		//小テスト得点
	double	rpt;		//レポート得点
	char	grade[3];	//成績評価
};

int main(void)
{
	int		i=0;					//カウンタ
	FILE	*fp;					//ファイルポインタ
	double	score;					//総合得点
	char	fname[]="record_25.txt",//入力ファイル名
			temp[256];				//インデックス行読み込みバッファ用配列
	struct prog2 Mech[SNUM]={0};

	//入力ファイルのオープン（読み込みモード）
	fp=fopen(fname,"r");
	if(fp==NULL){
		printf("Can't open %s!\n",fname);
		exit(1);	//強制終了
	}
	
	fgets(temp,256,fp);//インデックス部一行を配列tempに吐き出す
	
	//入力ファイルからデータの読み込み
	while(fscanf(fp,"%d%s%lf%lf%d",&Mech[i].ID,Mech[i].name,
		&Mech[i].mini,&Mech[i].rpt,&Mech[i].final)!=EOF){ i++; }

	fclose(fp);	//入力ファイルのクローズ

	//学生番号、項目別得点、総合得点、評価の表示
	printf("%-10s%-19s%10s%10s%10s%10s%10s\n","ID", "Name",
           "Mini", "Report", "Final", "Total", "Grade");

	for(i=0;i<SNUM;i++){
		score=Mech[i].mini+Mech[i].rpt+Mech[i].final;	//総合得点

		//成績判定（A+～D)
		if(score>=90)	strcpy(Mech[i].grade, "A+");
		else if(score>=80) strcpy(Mech[i].grade, "A");
		else if(score>=70) strcpy(Mech[i].grade, "B");
		else if(score>=60) strcpy(Mech[i].grade, "C");
		else	strcpy(Mech[i].grade, "D");

		//成績評価出力
		printf("%-10d%-19s%10.1f%10.1f%10d%10.1f%10s\n",Mech[i].ID,
        	Mech[i].name, Mech[i].mini, Mech[i].rpt, Mech[i].final,
			score, Mech[i].grade);
	}

	return 0;
}
