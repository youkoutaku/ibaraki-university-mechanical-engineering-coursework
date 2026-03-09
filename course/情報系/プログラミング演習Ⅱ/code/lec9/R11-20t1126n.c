//課題11 10進数から16進数への変換(再帰）
//20t1126n YANG GUANGZE

#include <stdio.h>

int show_hex(unsigned int x);

int main(void){
    unsigned int x;

    printf("10進数：");
    scanf("%d",&x);

    printf("16進数：0X");
    show_hex(x);

    return 0;
}

int show_hex ( unsigned int x ){
    unsigned int a, r;
    a = x/16;
    r = x%16;

    if( a > 0 ){
        return show_hex(a) + show_hex(r);
    }else{
        if(r >= 0 && r <= 9){
            printf("%d",r);
        }else{
            putchar(65 + r - 10);
        }
        return 0;
    }
}