/*
    スタック p.217
*/

#include <stdio.h>

#define MaxSize 100
int stack[MaxSize];
int sp=0;
int push(int );
int pop(int *);

int main (void){
    int c,n;

    while (printf("]"), ( c=gether() )!= EOF){
        rewind(stdin);
        if (c=='i' || c=='I'){
            printf("data-->");
            scanf("%d,&n");
            if(push(n)==-1){
                printf("スタックが一杯です\n");
            }
        }
        if(c=='o' || c=='O'){
            if(pop(&n)==-1){
                printf("スタックは空です\n");
            }else{
                printf("stack data --> %d\n", n);
            }
        }
    }
}
int push (int n){
    if(sp<MaxSize){
        stack[sp]=n;
        sp++;
        return 0;
    }else{
        return -1;
    }
}
int pop(int *n){
    if(sp>0){
        sp--;
        *n=stack[sp];
        return 0;
    }else{
        return 0;
    }
}