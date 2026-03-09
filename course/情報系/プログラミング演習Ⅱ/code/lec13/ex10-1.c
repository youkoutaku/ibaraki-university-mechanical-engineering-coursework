/*------------------------------------------------------------------*/
/*      		 			　<ex10-1.c> 					　　    */
/*　　　			　　　　　線形リスト 　　　　　　　　　 　　　　*/
/*                学生番号の昇順にチェーンを繋ぎ変える　　			*/
/*-----------------------------------------------------------------	*/
#include <stdio.h>
#include <stdlib.h>	//for exit(), calloc()

//Seiseki型の宣言
typedef struct{
	int		final;
	double	mini;
	double	rpt;
} Seiseki;

//Prog2型の宣言
typedef struct prog2{
	struct prog2	*next;		//次のノードへのポインタ
	int				ID; 		//学生番号
	char			name[20];	//名前
	Seiseki			sc;			//成績データ
} Prog2;

//関数のプロトタイプ宣言
Prog2 *Alloc_Node(void);
void print_list(Prog2 *start);
void make_list(Prog2 *start);

int main(void)
{
	Prog2 	dmy={NULL};		//NULLで初期化して終端マークにする
	Prog2	*start=&dmy;	//先頭管理用の構造体

	make_list(start);		//線形リストの生成

	print_list(start);		//線形リストのデータ表示

	return 0;
}

//線形リストの生成関数
void make_list(Prog2 *start)
{
		Prog2	*ip,		//forループ制御用
				*node,		//挿入ノードを指すポインタ
				wk={NULL};	//一時保存用

		while(1){

			//キーボードからのデータ入力
			printf("ID Number :"); 	scanf("%d",&wk.ID);
									if(wk.ID==EOF) break; //学生番号にEOF(-1)が入力されたら終了
			printf("Name      :"); 	scanf("%s", wk.name);
			printf("Final Exam:"); 	scanf("%d", &wk.sc.final);
			printf("Mini Test :"); 	scanf("%lf", &wk.sc.mini);
			printf("Report    :"); 	scanf("%lf", &wk.sc.rpt);

			//ノード1個分のメモリ領域を確保
			node=Alloc_Node();
	
			//ノードにデータを設定する
			*node=wk;

			//生成したノードをチェーンにはめ込む(学生番号の昇順)
			for(ip=start;ip->next!=NULL;ip=ip->next){
				if( node->ID < ip->next->ID){ 
					node->next=ip->next;
					ip->next=node;
					break;
				}
			}
			
			//学生番号が最大の場合チェーンの最後につなぐ
			if(ip->next==NULL){	//チェーンがNULLに行きついたら
				ip->next=node;		//最後尾にnodeをくっつける
				node->next=NULL;	//新たに最後尾のマーク(NULL)
			}
		}
}

//線形リストの全データを表示する関数
void print_list(Prog2 *start)
{
	Prog2 *ip;

	//チェーンをたどってノードの内容を表示する
	for(ip=start->next; ip!=NULL; ip=ip->next){
		printf("%-10d%-10s%10.1f%10.1f%10d\n",
			ip->ID,ip->name, ip->sc.mini, ip->sc.rpt, ip->sc.final);
	}
}

//ノード生成関数
Prog2 *Alloc_Node(void)
{
	Prog2 *pt;

	pt=(Prog2 *)calloc(1, sizeof(Prog2));	//Prog2型1個分動的に確保
	if(pt==NULL){
		printf("記憶領域の確保に失敗しました\n");
		exit(1);
	}

	return pt;
}