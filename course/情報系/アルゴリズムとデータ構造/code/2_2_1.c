//数値積分　台形則による定積分　
// [a~b]f(x) dx = h*( f(a)+f(a+h) )/2 + h*( f(a+h) +f(a+2h) )/2 +...+ h*( f( a+(n-1)h ) + f(b) )/2
// = h*{ ( f(a) + f(b) )/2 + f(a+h) + f(a+2h) + ...+ f( a+(n-1)h ) } 

#include <stdio.h>
#include <math.h>

#define f(x) (sqrt(4-(x)*(x))) //関数

int main (void){
    int k;
    double a,b,n,h,x,s,sum;

    printf("積分区間　A, B ?");
    scanf("%lf %lf", &a, &b);

    n=50;  //分割数
    h=(b-a)/n; //区間
    x=a; s=0;
    for(k=1; k <= n-1; k++){
        x=x+h;
        s=s+f(x);
    }
    sum = h*(f(a)+f(b)/2+s);
    printf("    /%f\n",b);
    printf("    |   sqrt(4-x*x) =%f\n", sum);
    printf("    /%f\n",a);

    return 0;
}

