/*------------------------------------------------------------------*/
/*                      <ex12-2.c> メイン関数	タブ4                 */
/*           □学生番号の昇順にチェーンを繋ぎ変える                 */
/*           □ファイルからデータを線形リストに読み込む             */
/*           □検索機能：学生番号、名前                             */
/*-----------------------------------------------------------------	*/
#include "myhead\ex12-2.h"

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