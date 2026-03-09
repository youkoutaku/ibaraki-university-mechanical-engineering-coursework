//課題19 自作関数の実体のうち、メニュー関数、検索関数（２つ）と抽出関数（１つ）が記述されたもの
//20t1126n YANG GUANGZE

#include "myhead\R19-20t1126n.h"

int menu(void){
    int ch;

    printf("/-----------------------------------------------------/\n");
	printf("/ 1.全データの出力                                    /\n");
	printf("/ 2.IDナンバーによる検索                              /\n");
	printf("/ 3.名前による検索                                    /\n");
	printf("/ 4.基礎代謝量(x)以上の抽出                           /\n");
	printf("/ 5.基礎代謝量(x)以上のを基礎代謝量の降順/昇順で抽出  /\n");
    printf("/ 6.終了                                              /\n");
	printf("/-----------------------------------------------------/\n");

	do{
		printf("選択項目を入力して下さい:"); scanf("%d", &ch);
	}while( ch<1 || ch >6);

	return ch;
}

void ID_Search(Eng *start){
	Eng 	*ip;
	int		key;

	printf("IDナンバー:");	scanf("%d", &key);

	for(ip=start->next; ip!=NULL; ip=ip->next){
		if(ip->ID==key){
			print_node(ip);	
			break;
		}
	}
	if(ip==NULL) printf("Not found!\n");
}

void name_Search(Eng *start){
	Eng 	*ip;
	char 	key[20];
	int		found=0;

	printf("名前:");	scanf("%s", key);

	for(ip=start->next; ip!=NULL; ip=ip->next){
		if(strcmp(ip->name,key)==0){
			print_node(ip);
			found++;
		}
	}
	if(found==0) printf("Not found!");
}

void print_Search(Eng *start){
    Eng *ip;
    int A;

    do{
		printf("基礎代謝量(x):"); scanf("%d", &A);
	}while(A == EOF);

    for(ip=start->next; ip!=NULL; ip=ip->next){
		if( bmr(ip) >= A){
            print_node(ip);
        }
	}
}
