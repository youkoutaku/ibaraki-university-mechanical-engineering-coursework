/* 練習4：文字列の交換[教科書シニア編p.178] */
#include <stdio.h>
#include <string.h>  /* strcpy関数を使うために必要なヘッダファイルを取り込む */

int main( void ){
  int i;

  char s1[4]= "abc"; /* char型配列による文字列の宣言と初期化 */
  char s2[4]= "xyz"; /* char型配列による文字列の宣言と初期化 */
  char *p1= "ABC"; /* ポインタによる文字列の宣言と初期化 */
  char *p2= "XYZ"; /* ポインタによる文字列の宣言と初期化 */
  
  char wks[4];
  char *wkp;

  printf("s1 = %s   s2 = %s\n", s1, s2);  /* 文字列の出力 */
  printf("--char型配列の文字列s1とs2を入れ替える--\n  char型配列の文字列の場合、srtcpy関数を使う必要がある\n");
  strcpy(wks, s1);  /* 配列名「s1」や「s2」はポインタ(配列の先頭要素のアドレス)を表す */
  strcpy(s1, s2);
  strcpy(s2, wks);
  printf("s1 = %s   s2 = %s\n", s1, s2);  /* 文字列の出力 */

  printf("\n"); 
  printf("p1 = %s   p2 = %s\n", p1, p2);  /* 文字列の出力 */
  printf("--ポインタ文字列p1とp2を入れ替える--\n  ポインタの場合、アドレスを交換すればよい\n");
  wkp = p1;  /* 教科書シニア編 p.180の下のプログラムを参考 */
  p1 = p2;
  p2 = wkp;
  printf("p1 = %s   p2 = %s\n", p1, p2); /* 文字列の出力 */

  return 0;
}

