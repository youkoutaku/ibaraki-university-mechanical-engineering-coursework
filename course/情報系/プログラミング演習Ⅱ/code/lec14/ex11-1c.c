/*------------------------------------------------------------------*/
/*							<ex11-1.c> タブ4						*/
/*			ex10-2.cのメイン関数のみが記述されたもの				*/
/*-----------------------------------------------------------------	*/
#include "C:\MinGW\prog2\myhead\ex11-1.h"

int main(void)
{
	Prog2 	dmy={NULL};		//NULLで初期化して終端マークにする
	Prog2	*start=&dmy;	//先頭管理用の構造体
	int		choice;			//選択項目番号

	load_data(start);
	
	do{
		choice=menu();
		switch(choice){
			case 1:
				ID_Search(start);
				break;
			case 2:
				name_Search(start);
				break;
		}
	}while(choice!=3); 	//choiceが3でない間は実行を繰り返す

	return 0;
}