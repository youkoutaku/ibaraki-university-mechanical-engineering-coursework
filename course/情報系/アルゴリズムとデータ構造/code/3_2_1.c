/*
    ƒ\[ƒg@Šî–{‘}“ü•û
*/

#include <stdio.h>
#include<stdlib.h>

#define N 100

int comps; // ”äŠr‰ñ”
int swaps; // ŒğŠ·‰ñ”

// ”äŠrŠÖ”
int comp(int x, int y) {
  ++comps;
  return x > y;
}

// ŒğŠ·ŠÖ”
void swap(int* px, int* py) {
  ++swaps;
  int tmp = *px;
  *px = *py;
  *py = tmp;
}

int main(void) {
    int a[N];
    int i,j;
     
    for(i=0; i<N; i++){
        a[i]=rand();
    }

    comps = 0;
    swaps = 0;

    for (i=1;i<N;i++) {
        for (j=i-1;j>= 0;j--){
            if ( comp(a[j], a[j+1]) > 0 ) { // ‚±‚±‚Å”äŠr
                swap(&a[j], &a[j+1]); // ‚±‚±‚ÅŒğŠ·
                //printf("%d %d %d %d %d %d\n", a[0],a[1],a[2],a[3],a[4],a[5]);
            }else{
                break;
            }
        }
    }

    for (i=0;i<N;i++)
        printf("%d ",a[i]);
    printf("\n");

    printf("%d comps / %d swaps\n", comps, swaps);
    return 0;
}