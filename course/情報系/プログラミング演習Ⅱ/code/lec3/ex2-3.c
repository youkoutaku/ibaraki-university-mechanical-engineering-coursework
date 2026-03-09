/* 練習3：2×2の1次変換を計算するプログラム */
#include <stdio.h>
#define N 2 /* 次元数は2 */
int main( void ){

  int i, j;
  double a[2][2] = { {0.5, -0.866}, {0.866, 0.5} };   /* 2×2配列(行列)Aの宣言と初期化 */
  double x[2], y[2];  /* 2次元配列(ベクトル)xとyの宣言 */

  x[0] = 3.3;  /* 配列xの第0成分の設定 */
  x[1] = 5.8;  /* 配列xの第1成分の設定 */

  for (i=0; i<N; i++)  {
    y[i] = 0.0;
    for (j=0; j<N; j++)  {
      y[i] += a[i][j] * x[j];  /* 配列yの第i成分の計算(プリントの式(4)参照) */
    }
    printf("y[%d] = %f\n", i, y[i]);
  }

  /*
  double A[2][3]={};
  double B[3][2]={};
  double C[2][2];
  
  for(i=0; i<2; i++){
    for(j=0; j<2;j++){
      for(int k=0;k<3;k++){
        c[i][j]+=a[i][k]*b[k][j];
      }
    }
  }


  */
  return 0;
}

