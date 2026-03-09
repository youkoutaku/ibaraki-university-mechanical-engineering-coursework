/*
    テーラー展開（ exp(x) ）
*/

#include<stdio.h>
#include<math.h>

double myexp(double);

int main (void){
    double x;
    printf("  x      myexp(x)        exp(x)\n");
    for (x= -40.0 ; x <= 40; x += 10){
        printf("%5.1lf%14.6g%14.6g\n", x, myexp(x), exp(x));
    }
    return 0;
}

double myexp(double x){
    double EPS=1e-08; //EPS葉必要な精度である。1e-8とすれば、精度は８桁程度である。
    double s=1.0, e=1.0, a, d;
    int k;

    a=fabs(x);
    for(k=1; k<=200; k++){
        d=s;
        e=e*a/k; 
        s+=e;
        if(fabs(s-d)<EPS*fabs(d)){  //fabs() は絶対値
            if( x>0 ){
                return s;
            }else{
                return 1.0/s;
            }
        } 
    }
    return 0;
}
