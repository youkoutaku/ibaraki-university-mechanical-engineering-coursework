//    練習問題１　Hornerの方法　　　オーバーフローを防ぐため
//    多項式f(x)=an*x^n + a(n-1)*x^(n-1) + ... + a1*x + a0

//    一般式で、fi = f(i-1)*x + a(n-1)
//              f0 = an


#include <stdio.h>

double fn(double, double *, int);

int main (void){
    double a[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double x;

    for(x=1.0; x<=5.0; x++){
        printf("fn(%lf)=%lf\n", x, fn(x, a, 4.0));
    }
    return 0;
}

double fn(double x, double a[], int n){
    double p;
    int i;

    p = a[n];
    for(i=n-1; i>=0; i--){
        printf("p=%lf",p);
        p= p*x + a[i];
        printf("p=%lf*%lf+%lf\n", p, x, a[i]);
    }
    return p;
}
