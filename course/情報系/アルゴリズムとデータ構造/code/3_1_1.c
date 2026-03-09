/*
    ソート　直接選択法
*/

#include <stdio.h>

#define N 6

int comps; // 比較回数
int swaps; // 交換回数

// 比較関数
int comp(int x, int y) {
  ++comps;
  return x < y;
}

// 交換関数
void swap(int* px, int* py) {
  ++swaps;
  int tmp = *px;
  *px = *py;
  *py = tmp;
}

int main(void) {
    int a[]={80, 41, 35, 90, 40, 20};
    int min,s,t,i,j;

    comps = 0;
    swaps = 0;

    for (i=0;i<N-1;i++) {
        min = a[i];
        s=i;
        for (j=i+1;j<N;j++){
            if ( comp(a[j], min) > 0 ) { // ここで比較
                min=a[j];
                s=j;    
            }
        }
        swap(&a[i], &a[s]); // ここで交換
        // printf("%d %d %d %d %d %d\n", a[0],a[1],a[2],a[3],a[4],a[5]);
    }

    for (i=0;i<N;i++)
        printf("%d ",a[i]);
    printf("\n");

    printf("%d comps / %d swaps\n", comps, swaps);
    return 0;
}