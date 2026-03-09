/* 練習5：ポインタの配列[教科書シニア編p.181] */
#include <stdio.h>
#include <string.h>  /* strcpy関数を使うために必要なヘッダファイルを取り込む */

int main( void ){
  int i;
  /* char型配列による多次元文字列の宣言と初期化 */
  /* ポインタ配列による多次元文字列の宣言と初期化 */
  char *wkp;
  char wk[10];

  printf("===<< 多次元文字配列の処理 >>===\n");
  for (i=0; i<3; i++)  {
    printf("ss[%d][] = %s\n", i, ss[i]);   /* 文字列ssの出力(ss[i]はポインタを表す) */
  }

  printf("--char型配列の文字列ss[0][]とss[1][]を入れ替える--\n  char型配列の文字列の場合、srtcpy関数を使う必要がある\n");
  strcpy(wk, ss[0]);  /* 配列名「ss[0]」や「ss[1]」はポインタ(配列の先頭要素のアドレス)を表す */
  strcpy(ss[0], ss[1]);
  strcpy(ss[1], wk);
  for (i=0; i<3; i++)  {
    printf("ss[%d][] = %s\n", i, ss[i]);  /* 文字列ss[i][]の出力 */
  }

  printf("\n");
  printf("===<< ポインタ配列の処理 >>===\n");
  for (i=0; i<3; i++)  {
    printf("ssp[%d] = %s\n", i, ssp[i]);   /* ポインタによる文字列sspの出力 */
  }

  printf("--ポインタ配列ssp[0]とssp[1]を入れ替える--\n  ポインタの場合、アドレスを交換すればよい\n");
  wkp = ssp[0];
  ssp[0] = ssp[1];
  ssp[1] = wkp;
  for (i=0; i<3; i++)  {
    printf("ssp[%d] = %s\n", i, ssp[i]);  /* ポインタによる文字列sspの出力 */
  }

  return 0;
}

