/*  fgets(入力)とfputs(出力)の使い方                             */
/*  ファイルのコピーを行う (教科書明 p.225をより簡単にしたもの)  */
#include <stdio.h>
#include <stdlib.h> /* exit() */

int main( void ){

  char ss[256];    /* 読み込んだ文字列を格納する変数(最大256文字)を宣言 */

  FILE *fpin, *fpout;                 /* ファイルポインタ変数の宣言 */
  fpin = fopen( "ex3-4_in.txt","r" );    /* 入力(read)用ファイルをオープン */
  fpout = fopen( "ex3-4_out.txt", "a" );  /* 出力(write)用ファイルをオープン */

  if (fpin == NULL)  {                /* 安全対策：入力用ファイルのオープンに失敗したときの処置 */
    printf("入力ファイルのオープンに失敗しました\n");
    exit(1);                         /* 途中でプログラムを終了させる */
  }

  if (fpout == NULL)  {              /* 安全対策：出力用ファイルのオープンに失敗したときの処置 */
    printf("出力ファイルのオープンに失敗しました\n");
    exit(1);                         /* 途中でプログラムを終了させる */
  }

  /* 入力ファイルの読み込みに失敗する(終了コードNULL)まで、一行ずつデータを読み込む */
  while (fgets(ss, 256, fpin) != NULL)  {  /* 読み込んだ行の中身を文字列ssに格納 */
    fputs(ss, fpout);                      /* 文字列ss(読み込んだデータ)を出力用ファイルへ出力 */
  }

  fputs("この行だけ追加しました", fpout);

  fclose(fpin);   /* 入力用ファイルをクローズ */
  fclose(fpout);  /* 出力用ファイルをクローズ */

  return 0;
}
