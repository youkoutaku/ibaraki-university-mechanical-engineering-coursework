/*
    フィボナッチ数(再帰)
*/


#include <stdio.h>

long fib(long);

int main(void){
    long n=5;

    printf("answer :%ld",fib(n));

    return 0;
}

long fib (long n){
    if(n==1 || n==2){
        printf("fib(%ld)を行う,return %ld\n", n, 1L);
        return 1L;
    }else{
        printf("fib(%ld)行う,return fib(%ld-1)+fib(%ld-2)\n", n, n, n);
        return fib(n-1)+fib(n-2);
    }
}