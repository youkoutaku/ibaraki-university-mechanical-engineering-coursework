//課題19 自作構造体の宣言や自作関数の定義が記述されたもの
//20t1126n YANG GUANGZE

#ifndef R19_20t1126n_H_INCLUDE
#define R19_20t1126n_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>	
#include <string.h>

typedef struct{
	char    gender;         //性別                    
    int     age;            //年齢
    double  weight;         //体重
} Data;

typedef struct Eng{
	struct Eng	*next;      //ポインタ
	int			ID;         //IDナンバー
	char		name[20];   //名前
	Data		data;       //入れ子
} Eng;

Eng *Alloc_Node(void);
int menu(void);
double bmr(Eng *ip);                    //基礎代謝量を計算する
void print_note(Eng *ip);               //基礎代謝量を含めてデータの出力

void load_data(Eng *start);             //データ入力、リストの作成
void print_list(Eng *start);            //データ表示(基礎代謝量がない)
void ID_Search(Eng *start);             //IDナンバー検索
void name_Search(Eng *start);           //名前検索
void print_Search(Eng *start);          //基礎代謝量(x)以上の検索
void print_Search_up_down(Eng *start);  //基礎代謝量(x)以上のを検索し、降順/昇順で表示する

#endif