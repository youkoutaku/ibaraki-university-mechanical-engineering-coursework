/*------------------------------------------------------------------*/
/*      		 		<ex10-3.c> 線形リスト				　　    */
/*                学生番号の昇順にチェーンを繋ぎ変える　　			*/
/*          ファイルからデータを線形リストに読み込む                */
/*　　　　　検索機能：学生番号、名前 、成績A+、成績C 　　　 　　　　*/
/*-----------------------------------------------------------------	*/
#include <stdio.h>
#include <stdlib.h>	
#include <string.h>

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
void print_node(Prog2 *node);
void load_data(Prog2 *start);
void name_Search(Prog2 *start);
void ID_Search(Prog2 *start);
void Extract_C(Prog2 *start);
void Extract_Ap(Prog2 *start);
int menu(void);

int main(void)
{
	Prog2 	dmy={NULL};		//NULLで初期化して終端マークにする
	Prog2	*start=&dmy;	//先頭管理用の構造体
	int		select;

	load_data(start);	//ファイルからデータを読み込み線形リストを構築
	
	do{
		select=menu();
		switch(select){
			case 1:
				ID_Search(start);
				break;
			case 2:
				name_Search(start);
				break;
			case 3:
				Extract_Ap(start);
				break;
			case 4:
				Extract_C(start);
				break;
		}
	}while(select!=5); 	//selectが5(終了)でない間は実行を繰り返す

	return 0;
}
//------------------------------------------------------------------------------
//							  menu関数									　  	
//																			　  
//	引  数：void                                                 　　　 		
//　戻り値：int														        	
//	機  能：選択画面を表示して、入力された選択項目の番号を返す　　 				
//------------------------------------------------------------------------------
int menu(void)
{
	int ch;

	printf("/-----------------------------------------/\n");
	printf("/ 1.Search by ID Number                   /\n");
	printf("/ 2.Search by Name                        /\n");
	printf("/ 3.Extracting the students of grade A+   /\n");
	printf("/ 4.Extracting the students of grade C    /\n");
	printf("/ 5.End                                   /\n");
	printf("/-----------------------------------------/\n");

	do{
		printf("Please enter your choice："); scanf("%d", &ch);
	}while( ch<1 || ch >5);

	return ch;
}
//------------------------------------------------------------------------------
//							  Extract_Ap 関数									
//																			　  
//	引  数：Prog2 *start                                                 　　　 
//　戻り値：void														        
//	機  能：ノードのデータから総合得点を計算し、その結果が90以上のデータ        
//          を出力する。最後に抽出したデータ数を出力する。				        
//------------------------------------------------------------------------------
void Extract_Ap(Prog2 *start)
{
	Prog2 	*ip;
	double	score;
	int		found=0;

	//チェーンをたどってノードを検索する
	for(ip=start->next; ip!=NULL; ip=ip->next){
		score=ip->sc.mini+ip->sc.rpt+ip->sc.final;
		if(score>=90){
			print_node(ip);
			found++;
		}
	}
	printf("There are %d students with grade A+.\n",found);
}
//------------------------------------------------------------------------------
//							  Extract_C 関数									　  
//																			　  
//	引  数：Prog2 *start                                                 　　　 
//　戻り値：void														        
//	機  能：ノードのデータから総合得点を計算し、その結果が60以上70未満のデータ  
//          を出力する。最後に抽出したデータ数を出力する。				        
//------------------------------------------------------------------------------
void Extract_C(Prog2 *start)
{
	Prog2 	*ip;
	double	score;
	int		found=0;

	//チェーンをたどってノードを検索する
	for(ip=start->next; ip!=NULL; ip=ip->next){
		score=ip->sc.mini+ip->sc.rpt+ip->sc.final;
		if(score<70 && score>=60){
			print_node(ip);
			found++;
		}
	}
	printf("There are %d students with grade C.\n",found);
}
//------------------------------------------------------------------------------
//							  ID_Search関数									　  
//																			　  
//	引  数：Prog2 *start                                                 　　　 
//　戻り値：void														        
//	機  能：リストからIDが検索キーkeyに一致するノードを検索し、　　　　 		
//　　　　　ノードのデータを出力する				                            
//------------------------------------------------------------------------------
void ID_Search(Prog2 *start)
{
	Prog2 	*ip;
	int		key;

	printf("ID Number:");	scanf("%d", &key);

	//チェーンをたどってノードを検索する
	for(ip=start->next; ip!=NULL; ip=ip->next){
		if(ip->ID==key){
			print_node(ip);	
			break;
		}
	}
	if(ip==NULL) printf("Not found!\n");
}
//------------------------------------------------------------------------------
//							  name_Search関数									
//																			　  
//	引  数：Prog2 *start                                                 　　　 
//　戻り値：void														        
//	機  能：リストからnameが検索キーkeyに一致するノードを検索し、　　　　 		
//　　　　　ノードのデータを出力する				                            
//------------------------------------------------------------------------------
void name_Search(Prog2 *start)
{
	Prog2 	*ip;
	char 	key[20];
	int		found=0;

	printf("Name:");	scanf("%s", key);

	//チェーンをたどってノードを検索する
	for(ip=start->next; ip!=NULL; ip=ip->next){
		if(strcmp(ip->name,key)==0){
			print_node(ip);
			found=1;
		}
	}
	if(found==0) printf("Not found!");
}
//------------------------------------------------------------------------------
//							load_data関数									　  
//																			　  
//	引  数：Prog2 *start                                                        
//　戻り値：void															    
//	機能：ファイルからデータを読み込み、線形リストを生成する				
//------------------------------------------------------------------------------
void load_data(Prog2 *start)
{
	FILE	*fp;		//ファイルポインタ
	char	fname[20],	//入力ファイル名
			temp[256];	//インデックス部用
	Prog2	*node, *ip, wk;

	//入力ファイル名の入力
	printf("Input file name:");	scanf("%s",fname);

	//入力ファイルのオープン（読み込みモード）
	fp=fopen(fname,"r");
	if(fp==NULL){
		printf("Can't open %s!\n",fname);
		exit(1);
	}

	//入力ファイルからデータの読み込み
	fgets(temp,256,fp);		//インデックス部一行を配列tempに吐き出す

	while(fscanf(fp,"%d%s%lf%lf%d", &wk.ID, wk.name, &wk.sc.mini, &wk.sc.rpt, &wk.sc.final)!=EOF){
			
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
			
			//最も学生番号が最大の場合チェーンの最後につなぐ
			if(ip->next==NULL){	//チェーンがNULLに行きついたら
				ip->next=node;		//最後尾にnodeをくっつける
				node->next=NULL;	//新たに最後尾のマーク(NULL)
			}
	}

	fclose(fp);	//ファイルのクローズ
}
//------------------------------------------------------------------------------
//							print_list関数									　  
//																			　  
//	引  数：Prog2 *start                                                          
//　戻り値：void															    
//	機能：リストlistの全ノードを画面に出力									    
//------------------------------------------------------------------------------
void print_list(Prog2 *start)
{
	Prog2 *ip;

	//チェーンをたどってノードの内容を表示する
	for(ip=start->next; ip!=NULL; ip=ip->next){
		printf("%-10d%-10s%10.1f%10.1f%10d\n",
			ip->ID,ip->name, ip->sc.mini, ip->sc.rpt, ip->sc.final);
	}
}
//------------------------------------------------------------------------------
//							print_node関数									　  
//																			　  
//	引  数：Prog2 *node                                                         
//　戻り値：void															    
//	機  能：nodeが指すノードデータを画面に出力									    
//------------------------------------------------------------------------------
void print_node(Prog2 *node)
{
	printf("%-10d%-10s%10.1f%10.1f%10d\n",
			node->ID, node->name, node->sc.mini, node->sc.rpt, node->sc.final);
}
//------------------------------------------------------------------------------
//							   Alloc_Node関数									
//																			　  
//	引  数：void                                                                
//　戻り値：Prog2 *												            
//	機  能：ノード1個分の記憶領域の確保し、確保した領域へのポインタを返す       
//------------------------------------------------------------------------------
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