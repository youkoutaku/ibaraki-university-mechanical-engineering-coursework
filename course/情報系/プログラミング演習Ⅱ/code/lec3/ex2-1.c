/* 練習1：多数のデータの合計、平均値、最大値を計算するプログラム */
#include <stdio.h>

int main( void ){

  int i, n;
  double height[5] = {172.9, 167.3, 184.5, 176.9, 170.1};  /* 要素数5の配列の宣言と初期値代入 */
  double sum, avr, max;

  n = 5; /* データの個数を代入 */

  sum = 0.0;
  for (i=0; i<n; i++)  {
    printf("%f\n", height[i]); /* i番目の配列要素の中身を確認のため出力 */
    sum += height[i];          /* i番目のデータを順に加算していく */
  }
  avr = sum / (double) n;  /* 平均値の計算 */
  printf("総和 = %f 平均値 = %f\n", sum, avr);

  max = height[0];       /* 最大値の候補maxに最初の配列のデータを代入しておく */
  for (i=1; i<n; i++)  { /* 2番目以降のデータを比較していく */
    if(height[i] > max)  max = height[i];  /* もしi番目のデータがmaxの中身より大きければ、その値をmaxに保存 */
  }
  printf("最大値 = %f\n", max);

  return 0;
}

