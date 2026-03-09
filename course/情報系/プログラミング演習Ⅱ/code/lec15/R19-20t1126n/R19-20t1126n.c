//課題19 メイン関数が記述されたもの
//20t1126n YANG GUANGZE
//入力ファイル：eng.txt

#include "myhead\R19-20t1126n.h"

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