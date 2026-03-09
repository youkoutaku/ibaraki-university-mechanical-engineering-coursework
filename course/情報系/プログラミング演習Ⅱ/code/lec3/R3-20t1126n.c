//課題3 アフィン変換を計算するプログラム
//20T1126N YANG GUANGZE(楊広沢)

#include <stdio.h>
#define N 3

int main(void){
    int i,j;
    double a[3][3] = {{5.2, 2.7, 3.5}, {-1.2, 9.3, -1.2}, {0.3, 7.5, -1.5}};
    double x[3] = {3.6, 1.4, -4.5};
    double b[3] = {3.2, 2.7, -1.9};
    double y[3] = {0};

    for(i=0; i<3; i++){
        y[i] = b[i];
        for(j=0; j<N; j++){
            y[i] += a[i][j] * x[j];
        }
        printf("y[%d] = %lf\n", i,y[i]);
    }
    return 0;
}