/* 練習2：データを小さい順に並び換えるプログラム　[配列の応用] */
#include <stdio.h>

int main( void ){

  int data[8] = {32, 55, 16, 84, 7, 22, 49, 11}; /* データを配列に格納する */ 
  int a, i, j, n = 8;  /* nはデータ数 */

  for (i=0; i<n; i++)  {
    printf("%d ", data[i]);  /* 配列の各要素を画面に出力 */
  }
  printf("\n");

  for (i=0; i<n-1; i++)  {   /* i=0(最初のデータ)からi=n-2まで繰り返す */
    for (j=i+1; j<n; j++)  { /* j=i+1からj=n-1(最後のデータ)まで繰り返す */
      if(data[i] > data[j])  {  /* もしdata[i]>data[j]なら中身を交換し、data[i]を小さい状態にする */
        a = data[i];         /* data[i]の中身を一時、aに保存する */
        data[i] = data[j];   /* data[j]の中身をdata[i]に移す */
        data[j] = a;         /* 保存していたaの中身をdata[j]に移す */
      }
    }
  }

  printf("小さい順に並び換えた後のデータ列\n");
  for (i=0; i<n; i++)  {
    printf("%d ", data[i]);  /* 結果を画面に出力 */
  }
  printf("\n");

  return 0;
}

