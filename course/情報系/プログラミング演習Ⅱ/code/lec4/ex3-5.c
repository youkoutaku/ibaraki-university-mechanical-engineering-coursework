/*  練習5：データファイルから名前、年齢を読み取り、年齢の低い順に並び替える */
#include <stdio.h>
#include <string.h> /* strcpy関数を使用するために必要 */

int main( void ){

  char ss[12], name[100][12];  /* 11文字までの名前を100人まで処理可能 */
  int a, age[100];             /* 100人までの年齢を処理可能 */
  int i, j,n;

  FILE *fpin, *fpout;                  /* ファイルポインタ変数の宣言 */
  fpin = fopen("ex3-5_in.txt", "r");    /* 入力(read)用ファイルをオープン */
  fpout = fopen("ex3-5_out.txt", "w");  /* 出力(write)用ファイルをオープン */

  if (fpin == NULL)  {                /* 安全対策：入力用ファイルのオープンに失敗したときの処置 */
    printf("入力ファイルのオープンに失敗しました");
    return 0;                         /* 途中でプログラムを終了させる */
  }

  if (fpout == NULL)  {              /* 安全対策：出力用ファイルのオープンに失敗したときの処置 */
    printf("出力ファイルのオープンに失敗しました");
    return 0;                         /* 途中でプログラムを終了させる */
  }

  /* 入力ファイル中にEOF(End of File)が現れるまで、形式に従ってデータを順に読み込む */
  n=0;
  while (fscanf(fpin, "%s %d", name[n], &age[n]) != EOF)  {
    printf("%-8s %d\n", name[n], age[n]);  /* 確認のため、読み込んだデータを画面へ出力 */
    n++;
  }
  printf("%d人分のデータがあります\n", n);

  for (i=0; i<n-1; i++)  {
    for (j=i+1; j<n; j++)  {
      if (age[i] > age[j])  {  /* もしage[i]がage[j]より大きければ、名前と年齢を入れ替える */
        a = age[i];                /* age[i]とage[j]の中身を入れ替える */
        age[i] = age[j];
        age[j] = a;

        strcpy(ss, name[i]);       /* name[i][]とname[j][]の中身を入れ替える */
        strcpy(name[i], name[j]);
        strcpy(name[j], ss);
      }
    }
  }

  for (i=0; i<n; i++)  {
    fprintf(fpout, "%-8s %d\n", name[i], age[i]);  /* 結果を出力ファイルへ出力 */
  }

  fclose(fpin);   /* 入力用ファイルをクローズ */
  fclose(fpout);  /* 出力用ファイルをクローズ */

  return 0;
}