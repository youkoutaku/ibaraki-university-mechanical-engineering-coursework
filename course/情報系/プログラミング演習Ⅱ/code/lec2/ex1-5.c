#include <stdio.h>

int main( void )
{
  int i, j;
  
  for( i=-20; i<=20; i=i+2 )  { /* iを-20～20まで2ずつ増やす */
    printf("%d ", i);
  }
  printf("\n------\n");

  for( i=1; i<10; i++ )  {   /* i=1～9までループさせる */
    for( j=1; j<10; j++ )  { /* j=1～9までループさせる */
      printf("%d ", i*j);    /* i*jを計算し、その値を出力 */
    } 
    printf("\n");  /* jのループが終わる度に改行(\n)する */
  }

  return 0;
}

