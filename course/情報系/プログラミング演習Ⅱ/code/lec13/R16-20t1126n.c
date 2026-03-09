//課題16 線形リストを用いる基礎代謝量
//20t1126n YANG GUANGZE
//gcc -Wall -o R16-20t1126n R16-20t1126n.c
//入力ファイル：eng.txt

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

void load_data(Eng *start)
{
    FILE    *fp;
    char    fname[20];
    Eng	*node, *ip, wk;

	printf("Input file name:");	scanf("%s",fname);

	fp=fopen(fname,"r");
	if(fp==NULL){
		printf("Can't open %s!\n",fname);
		exit(1);
	}

	while(fscanf(fp,"%d %s %c %d %lf", &wk.ID, wk.name, &wk.data.gender, &wk.data.age, &wk.data.weight)!=EOF){
			
			node=Alloc_Node();
			*node=wk;

			for(ip=start;ip->next!=NULL;ip=ip->next){
				if( node->ID < ip->next->ID){ 
					node->next=ip->next;
					ip->next=node;
					break;
				}
			}
			
			if(ip->next==NULL){
				ip->next=node;
				node->next=NULL;
			}
	}
	fclose(fp);	//ファイルのクローズ
}

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

void print_node(Eng *ip){
	printf("%-8d%-8s%10c%10d%10.1lf%10.1lf\n",
			ip->ID,ip->name, ip->data.gender, ip->data.age, ip->data.weight, bmr(ip) );
}

double bmr(Eng *obj){
    double B=0.0;

    if(obj->data.gender == 'M' ){   //男性の場合
        if( obj->data.age >= 15 && obj->data.age <= 17){
            B = 27.0*obj->data.weight;
        }else if( obj->data.age >= 18 && obj->data.age <= 29){
            B = 24.0*obj->data.weight;
        }else if( obj->data.age >= 30 && obj->data.age <= 49){
            B = 22.3*obj->data.weight;
        }else if( obj->data.age >= 50 && obj->data.age <= 69){
            B = 21.5*obj->data.weight;
        }else{
            B = 0.0;
        }
    }
    if( obj->data.gender =='F'){    //女性の場合
       if( obj->data.age >= 15 && obj->data.age <= 17){
            B = 25.3 * (obj->data.weight);
        }else if(obj->data.age >= 18 && obj->data.age <= 29){
            B = 23.6*obj->data.weight;
        }else if(obj->data.age >= 30 && obj->data.age <= 49){
            B = 21.7*obj->data.weight;
        }else if(obj->data.age >= 50 && obj->data.age <= 69){
            B = 20.7*obj->data.weight;
        }else{
            B = 0.0;
        }
    }
    return B;
}

Eng *Alloc_Node(void){
	Eng *pt;

	pt=(Eng *)calloc(1, sizeof(Eng));	
	if(pt==NULL){
		printf("記憶領域の確保に失敗しました\n");
		exit(1);
	}

	return pt;
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

void print_list(Eng *start){
    Eng *ip;

	for(ip=start->next; ip!=NULL; ip=ip->next){
		printf("%-8d%-8s%10c%10d%10.1lf\n",
			ip->ID,ip->name, ip->data.gender, ip->data.age, ip->data.weight);
	}
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

void print_Search_up_down(Eng *start){
    Eng *ip, *jp;
    double min;
    int A, B;
    int i, j, k, N;

    do{
		printf("基礎代謝量(x):"); scanf("%d", &A);
	}while(A == EOF);

    do{
		printf("降順(入力：1) 昇順(入力：2)　:"); scanf("%d", &B);
	}while(B == EOF);

    i=0;
    for(ip=start->next; ip!=NULL; ip=ip->next){
        i++;
	}
    N=i;    //データの総数
    Eng *a[N]; //ポインタ配列

    i=0;
    for(ip=start->next; ip!=NULL; ip=ip->next){
        a[i]=ip;
        i++;
	}

    for(i=0; i<N-1; i++){
        min = bmr(a[i]);
        k=i;
        for(j=i+1; j<N; j++){
            if( bmr(a[j]) > min){
                min = bmr(a[j]);
                k=j;
            }
        }
        jp=a[i]; a[i]=a[k]; a[k]=jp;
    }   //直接選択法

    if(B==1){       //降順
        for(i=0; i<N; i++){
            if(bmr(a[i]) >= A){
                print_node(a[i]);
            }
        }
    }else if(B==2){ //昇順
        for(i=N-1; i>=0; i--){
            if(bmr(a[i]) >= A){
                print_node(a[i]);
            }
        }
    }else{
        printf("エラー\n");
    }
}