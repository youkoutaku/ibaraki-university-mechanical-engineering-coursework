/*------------------------------------------------------------------*/
/*                               <ex12-2.h>                         */
/*                 自作構造体の宣言と自作関数の定義を記述           */
/*                 ex12-2.cとex12-2_func.cに読み込まれる            */
/*-----------------------------------------------------------------	*/
#ifndef EX12_2_H_INCLUDED
#define EX12_2_H_INCLUDED

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
int menu(void);

#endif