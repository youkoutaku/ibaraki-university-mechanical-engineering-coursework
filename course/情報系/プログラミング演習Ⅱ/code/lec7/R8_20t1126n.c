//課題8　基礎代謝量を計算するプログラム
//20t1126n YANG GUANGZE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 15

typedef struct {
    int     ID;
    char    name[12];
    char    gender; 
    int     age;
    double  weight;
    double  bmr;
} Eng;

void load_data(char *fname, Eng *obj);
void bmr_eval( Eng *obj);
void sort_data(char *fname, Eng *obj);

int main(void)
{
    char in[] = "eng.txt";
    char out[] = "R8_out.txt";
    Eng person[N]={0};

    load_data(in, person);

    bmr_eval(person);

    sort_data(out, person);

    return 0;
}

void load_data(char *fname, Eng *obj)
{
    FILE *fp;
    int i=0;
    
    fp=fopen(fname,"r");
	if(fp==NULL){
		printf("Can't open %s!\n",fname);
		exit(1);	
	}

    while(fscanf(fp, "%d   %s %c  %d  %lf\n", &(obj+i)->ID, (obj+i)->name,
      &(obj+i)->gender, &(obj+i)->age, &(obj+i)->weight)!=EOF){
        printf("%-8d%-8s%10c%10d%10.1lf\n", (obj+i)->ID, (obj+i)->name,
          (obj+i)->gender, (obj+i)->age, (obj+i)->weight);
        i++;
    }

    fclose(fp);
}

void bmr_eval(Eng *obj)
{
    int i;
    for(i=0; i<N; i++){
        if((obj+i)->gender == 'M' ){
            if( (obj+i)->age >= 15 && (obj+i)->age <= 17){
                (obj+i)->bmr = 27.0*(obj+i)->weight;
            }else if((obj+i)->age >= 18 && (obj+i)->age <= 29){
                (obj+i)->bmr = 24.0*(obj+i)->weight;
            }else if((obj+i)->age >= 30 && (obj+i)->age <= 49){
                (obj+i)->bmr = 22.3*(obj+i)->weight;
            }else if((obj+i)->age >= 50 && (obj+i)->age <= 69){
                (obj+i)->bmr = 21.5*(obj+i)->weight;
            }else{
                (obj+i)->bmr = 0.0;
            }
            }
        if((obj+i)->gender =='F'){
           if((obj+i)->age >= 15 && (obj+i)->age <= 17){
                (obj+i)->bmr = 25.3*(obj+i)->weight;
            }else if((obj+i)->age >= 18 && (obj+i)->age <= 29){
                (obj+i)->bmr = 23.6*(obj+i)->weight;
            }else if((obj+i)->age >= 30 && (obj+i)->age <= 49){
                (obj+i)->bmr = 21.7*(obj+i)->weight;
            }else if((obj+i)->age >= 50 && (obj+i)->age <= 69){
                (obj+i)->bmr = 20.7*(obj+i)->weight;
            }else{
                (obj+i)->bmr = 0.0;
            }
        }
    }
}

void sort_data(char *fname, Eng *obj)
{
    FILE    *fp;
    int     i,j;	
	Eng     *wk,
            *p[N]={NULL};

    for(i=0; i<N; i++) p[i]=obj+i;

	for(i=0;i<N-1;i++){		
		for(j=i+1;j<N;j++){
			if( (p[i]->bmr) < (p[j]->bmr) ){
				wk=p[i];
				p[i]=p[j];
				p[j]=wk;
			}
		}
	}

    fp=fopen(fname, "w");
    if(fp==NULL){
		printf("Can't open %s!\n",fname);
		exit(1);	
	}

    for(i=0; i<N; i++){
        fprintf(fp,"%-8d%-8s%10c%10d%10.1lf%10.1lf\n", p[i]->ID, p[i]->name,
            p[i]->gender, p[i]->age, p[i]->weight, p[i]->bmr);
    }

    fclose(fp);
}