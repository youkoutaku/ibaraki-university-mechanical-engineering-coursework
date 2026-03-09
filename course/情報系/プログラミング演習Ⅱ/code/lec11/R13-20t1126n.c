//課題13 ポインタのプログラム1
//20t1126n YANG GUANGZE

#include <stdio.h>

void pointer(char (*y)[9] );

int main(void){
	char 	x[3][9]={"YANG", "GUANGZE", "19991102"}; 	
	int 	i;

    printf("\nx=%p sizeof(x)=%d\n",x,sizeof(x));

	for(i=0;i<3;i++){
		printf("&x[%d]=%p x[%d]=%p %s\n", i, &x[i], i, x[i], x[i]);
    }

    pointer(x);

    return 0;
}

void pointer (char (*y)[9]){
    int i;

	printf("\n&y=%p y=%p sizeof(y)=%d\n", &y, y, sizeof(y));

    for(i=0;i<3;i++){
		printf("&y[%d]=%p y[%d]=%p %s\n",i,&y[i],i,y[i],y[i]);
    }
}
