//課題18 自作構造体の宣言と自作 関数の定義（プロトタイプ宣言）が記述されたもの
//20t1126n YANG GUANGZE
//gcc -Wall -o R18-20t1126n R18-20t1126n.c
//入力ファイル：eng.txt

#include "myhead\R18-20t1126n.h"
#include "R18-20t1126n_func.c"

int main(void)
{
    Eng dmy={NULL};
    Eng *start=&dmy;
    int select;

    load_data(start);
    do{
		select=menu();
		switch(select){
			case 1:
				print_list(start);
				break;
			case 2:
				ID_Search(start);
				break;
			case 3:
                name_Search(start);
				break;
			case 4:
                print_Search(start);
				break;
            case 5:
                print_Search_up_down(start);
                break;
		}
	}while(select!=6); 	

    return 0;
}